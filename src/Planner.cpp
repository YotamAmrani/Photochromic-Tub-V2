#include "Planner.h"
#include <Arduino.h>
bool flag = false;
Planner::Planner(StepperController *stepper_c, struct segment_plan *seg_pl)
{
    stepper_c_ = stepper_c;
    segment_plan_ = seg_pl;
    current_drawing_ = nullptr;
    current_segment_ = 0;
    is_segment_printing_ = false;
    finished_drawing_ = true;
}

void Planner::print_stepper()
{
    const int *pos = stepper_c_->get_steps_count();
    Serial.println("POS:");
    Serial.print(pos[X_AXIS]);
    Serial.print(",");
    Serial.print(pos[Y_AXIS]);
    Serial.print(",");
    Serial.println(pos[Z_AXIS]);
}

void Planner::init_segment_plan(const int *target_pos)
{
    Serial.println("Loading segment.");
    segment_plan_->current_position = stepper_c_->get_steps_count();
    segment_plan_->target_position[X_AXIS] = target_pos[X_AXIS];
    segment_plan_->target_position[Y_AXIS] = target_pos[Y_AXIS];
    segment_plan_->target_position[Z_AXIS] = target_pos[Z_AXIS];
    segment_plan_->dx = abs(segment_plan_->current_position[X_AXIS] - target_pos[X_AXIS]);
    segment_plan_->dy = abs(segment_plan_->current_position[Y_AXIS] - target_pos[Y_AXIS]);
    segment_plan_->dz = abs(segment_plan_->current_position[Z_AXIS] - target_pos[Z_AXIS]);
    segment_plan_->dominant_axis = max(max(segment_plan_->dx, segment_plan_->dy), segment_plan_->dz);
    segment_plan_->x_step_value = 0;
    segment_plan_->y_step_value = 0;
    segment_plan_->z_step_value = 0;
    // Set steps directions
    segment_plan_->current_direction_mask = get_line_direction_mask(segment_plan_->current_position, segment_plan_->target_position);
    segment_plan_->current_step_mask = 0;
    // _segment_plan->segment_is_enabled = false;
}

void Planner::print_segment()
{
    Serial.print("current step mask: ");
    Serial.print(segment_plan_->current_step_mask);
    Serial.print(",");
    Serial.println(segment_plan_->current_direction_mask);
    Serial.print("current pos: ");
    Serial.print(segment_plan_->current_position[X_AXIS]);
    Serial.print(",");
    Serial.print(segment_plan_->current_position[Y_AXIS]);
    Serial.print(",");
    Serial.println(segment_plan_->current_position[Z_AXIS]);

    Serial.print("target pos: ");
    Serial.print(segment_plan_->target_position[X_AXIS]);
    Serial.print(",");
    Serial.print(segment_plan_->target_position[Y_AXIS]);
    Serial.print(",");
    Serial.println(segment_plan_->target_position[Z_AXIS]);
    Serial.print("deltas: ");
    Serial.print(segment_plan_->dx);
    Serial.print(",");
    Serial.print(segment_plan_->dy);
    Serial.print(",");
    Serial.print(segment_plan_->dz);
    Serial.print(",");
    Serial.println(segment_plan_->dominant_axis);
    Serial.print("step values : ");
    Serial.print(segment_plan_->x_step_value);
    Serial.print(",");
    Serial.print(segment_plan_->y_step_value);
    Serial.print(",");
    Serial.println(segment_plan_->z_step_value);

    Serial.println("--------------------------");
}

void Planner::print_steps()
{
    Serial.println("steps values:");
    Serial.print(segment_plan_->x_step_value);
    Serial.print(",");
    Serial.print(segment_plan_->y_step_value);
    Serial.print(",");
    Serial.println(segment_plan_->z_step_value);
    Serial.println("_________________________________");
}

void Planner::print_segment_positions()
{
    Serial.print("current pos: ");
    Serial.print(segment_plan_->current_position[X_AXIS]);
    Serial.print(",");
    Serial.print(segment_plan_->current_position[Y_AXIS]);
    Serial.print(",");
    Serial.println(segment_plan_->current_position[Z_AXIS]);
    Serial.print("target pos: ");
    Serial.print(segment_plan_->target_position[X_AXIS]);
    Serial.print(",");
    Serial.print(segment_plan_->target_position[Y_AXIS]);
    Serial.print(",");
    Serial.println(segment_plan_->target_position[Z_AXIS]);
    Serial.println("______________________________________");
}

void Planner::move_to_position()
{
    const int *current_position = stepper_c_->get_steps_count();
    // if (
    //     segment_plan_->current_position[X_AXIS] != current_position[X_AXIS] ||
    //     segment_plan_->current_position[Y_AXIS] != current_position[Y_AXIS] ||
    //     segment_plan_->current_position[Z_AXIS] != current_position[Z_AXIS])
    // {
    //     Serial.println("WTF");
    // }
    if (current_position[X_AXIS] != segment_plan_->target_position[X_AXIS] ||
        current_position[Y_AXIS] != segment_plan_->target_position[Y_AXIS] ||
        current_position[Z_AXIS] != segment_plan_->target_position[Z_AXIS])
    {
        /** START PRINTING **/
        if (!is_segment_printing_)
        {
            is_segment_printing_ = true;
            stepper_c_->set_enable(true);
            stepper_c_->set_direction(segment_plan_->current_direction_mask);
        }

        segment_plan_->current_step_mask = 0;
        // Extract X step value
        if (current_position[X_AXIS] != segment_plan_->target_position[X_AXIS])
        {
            if (segment_plan_->dx && (segment_plan_->x_step_value >= segment_plan_->dominant_axis))
            {
                segment_plan_->current_step_mask = segment_plan_->current_step_mask | (1 << X_AXIS);
                segment_plan_->x_step_value -= segment_plan_->dominant_axis;
            }
            segment_plan_->x_step_value += segment_plan_->dx;
        }
        // Extract Y step value
        if (current_position[Y_AXIS] != segment_plan_->target_position[Y_AXIS])
        {
            if (segment_plan_->dy && (segment_plan_->y_step_value >= segment_plan_->dominant_axis))
            {
                segment_plan_->current_step_mask = segment_plan_->current_step_mask | (1 << Y_AXIS);
                segment_plan_->y_step_value -= segment_plan_->dominant_axis;
            }
            segment_plan_->y_step_value += segment_plan_->dy;
        }
        // Extract Z step value
        if (current_position[Z_AXIS] != segment_plan_->target_position[Z_AXIS])
        {
            if (segment_plan_->dz && (segment_plan_->z_step_value >= segment_plan_->dominant_axis))
            {
                segment_plan_->current_step_mask = segment_plan_->current_step_mask | (1 << Z_AXIS);
                segment_plan_->z_step_value -= segment_plan_->dominant_axis;
            }
            segment_plan_->z_step_value += segment_plan_->dz;
        }
        if (current_position[Z_AXIS] == 1)
        {
            print_segment_positions();
            print_stepper();
            // this->print_segment();
        }

        stepper_c_->move_step(segment_plan_->current_step_mask, segment_plan_->current_direction_mask);
    }
    else
    {
        // Serial.println("got here");
        stepper_c_->set_enable(false);
        is_segment_printing_ = false;
    }
}

int Planner::get_line_direction_mask(const int *point1, const int *point2)
{
    const int x_direction_sign = sgn(point2[X_AXIS] - point1[X_AXIS]);
    const int y_direction_sign = sgn(point2[Y_AXIS] - point1[Y_AXIS]);
    const int z_direction_sign = sgn(point2[Z_AXIS] - point1[Z_AXIS]);
    int current_direction_mask = 0;
    if (x_direction_sign && x_direction_sign < 0)
    {
        current_direction_mask = current_direction_mask | (1 << X_AXIS);
    }
    if (y_direction_sign && y_direction_sign < 0)
    {
        current_direction_mask = current_direction_mask | (1 << Y_AXIS);
    }
    if (z_direction_sign && z_direction_sign < 0)
    {
        current_direction_mask = current_direction_mask | (1 << Z_AXIS);
    }
    return current_direction_mask;
}

// void Planner::load_drawing(double drawing_to_plot[][N_AXIS], int drawing_size)
// {

//     Serial.println("Start printing!");
//     finished_drawing_ = false;
//     current_drawing_ = drawing_to_plot;
//     current_drawing_size_ = drawing_size;
//     stepper_c_->set_steps_rate(700);
// }

void Planner::load_drawing(Drawing *current_drawing)
{
    finished_drawing_ = false;
    current_drawing_ = current_drawing;
    stepper_c_->set_steps_rate(current_drawing->drawing_speed_);
    Serial.println("Start ploting drawing");
    Serial.print("first segment:");
    Serial.print(pgm_read_word(&current_drawing_->segments_[current_segment_][X_AXIS]));
    Serial.print(",");
    Serial.print(pgm_read_word(&current_drawing_->segments_[current_segment_][Y_AXIS]));
    Serial.print(",");
    Serial.println(pgm_read_word(&current_drawing_->segments_[current_segment_][Z_AXIS]));
}

void Planner::plot_drawing()
{
    if (!finished_drawing_)
    {
        // Serial.println(current_drawing_size_);
        if (!is_segment_printing_ && current_segment_ < current_drawing_->drawing_size_)
        {
            // Converting current target position into steps
            // this is a local variable, it may be flushed after a while?
            const int target_to_steps[N_AXIS] = {
                int(mm_to_steps(X_STEPS_PER_MM, pgm_read_word(&current_drawing_->segments_[current_segment_][X_AXIS]))),
                int(mm_to_steps(Y_STEPS_PER_MM, pgm_read_word(&current_drawing_->segments_[current_segment_][Y_AXIS]))),
                int(mm_to_steps(Z_STEPS_PER_MM, pgm_read_word(&current_drawing_->segments_[current_segment_][Z_AXIS])))};

            // start of segment
            init_segment_plan(target_to_steps);
            print_segment_positions();
            // print_segment();
            // print_stepper();
            move_to_position();
            Serial.print("Finished segment: ");
            Serial.println(current_segment_);

            current_segment_++;
        }
        else if (is_segment_printing_)
        {
            move_to_position();
        }
        else if (current_segment_ == current_drawing_->drawing_size_)
        {
            reset_drawing();
        }
    }
}

bool Planner::is_drawing_finished()
{
    return finished_drawing_;
}

void Planner::reset_drawing()
{
    print_stepper();
    Serial.println("Finished plotting drawing");
    // Serial.println(current_drawing_->drawing_name_);
    current_drawing_ = nullptr;
    current_segment_ = 0;
    finished_drawing_ = true;
    is_segment_printing_ = false;
}

void Planner::test_print()
{
    Serial.print("testing: ");
    Serial.println(current_drawing_->drawing_size_);
    for (int i = 0; i < current_drawing_->drawing_size_; i++)
    {
        Serial.print(pgm_read_word(&(current_drawing_->segments_)[i][X_AXIS]));
        Serial.print(",");
        Serial.print(pgm_read_word(&(current_drawing_->segments_)[i][Y_AXIS]));
        Serial.print(",");
        Serial.println(pgm_read_word(&(current_drawing_->segments_)[i][Z_AXIS]));
    }
}