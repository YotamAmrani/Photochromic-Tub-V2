#include "Planner.h"
#include <Arduino.h>

Planner::Planner(Stepper (&axis)[N_AXIS])
{
    axis_ = axis;
    current_drawing_ = nullptr;
    current_segment_ = 0;
    is_segment_printing_ = false;
    finished_drawing_ = true;
}

void Planner::init_segment_plan(const int *target_pos)
{
    Serial.println("Loading segment.");
    float dx = abs(axis_[X_AXIS].get_steps_count() - target_pos[X_AXIS]);
    float dy = abs(axis_[Y_AXIS].get_steps_count() - target_pos[Y_AXIS]);
    float dz = abs(axis_[Z_AXIS].get_steps_count() - target_pos[Z_AXIS]);
    float dominant_axis = max(max(dx, dy), dz);

    // set directions
    axis_[X_AXIS].set_direction(sgn(target_pos[X_AXIS] - axis_[X_AXIS].get_steps_count()));
    axis_[Y_AXIS].set_direction(sgn(target_pos[Y_AXIS] - axis_[Y_AXIS].get_steps_count()));
    axis_[Z_AXIS].set_direction(sgn(target_pos[Z_AXIS] - axis_[Z_AXIS].get_steps_count()));

    // set steps_rate
    int x_steps_rate = int((dominant_axis / dx) * STEPS_RATE);
    int y_steps_rate = int((dominant_axis / dy) * STEPS_RATE);
    int z_steps_rate = int((dominant_axis / dz) * STEPS_RATE);
    axis_[X_AXIS].set_steps_rate(x_steps_rate);
    axis_[Y_AXIS].set_steps_rate(y_steps_rate);
    axis_[Z_AXIS].set_steps_rate(z_steps_rate);

    // Serial.print("directions : ");
    // Serial.print(sgn(target_pos[X_AXIS] - axis_[X_AXIS].get_steps_count()));
    // Serial.print(",");
    // Serial.print(sgn(target_pos[Y_AXIS] - axis_[Y_AXIS].get_steps_count()));
    // Serial.print(",");
    // Serial.println(sgn(target_pos[Z_AXIS] - axis_[Z_AXIS].get_steps_count()));

    // Serial.print("directions : ");
    // Serial.print(axis_[X_AXIS].get_direction());
    // Serial.print(",");
    // Serial.print(axis_[Y_AXIS].get_direction());
    // Serial.print(",");
    // Serial.println(axis_[Z_AXIS].get_direction());
    // Serial.println("________________________");
    // Serial.print("deltas : ");
    // Serial.print((dominant_axis / dx));
    // Serial.print(",");
    // Serial.print(dominant_axis / dy);
    // Serial.print(",");
    // Serial.println(dominant_axis / dz);
    // Serial.println("________________________");
    Serial.print("steps rate : ");
    Serial.print(x_steps_rate);
    Serial.print(",");
    Serial.print(y_steps_rate);
    Serial.print(",");
    Serial.println(z_steps_rate);
    Serial.println("________________________");
}

void Planner::move_to_position(const int *target_position)
{
    const int current_position[N_AXIS] = {
        axis_[X_AXIS].get_steps_count(),
        axis_[Y_AXIS].get_steps_count(),
        axis_[Z_AXIS].get_steps_count(),
    };
    // Print position
    // Serial.print("Current position: ");
    // Serial.print(current_position[X_AXIS]);
    // Serial.print(",");
    // Serial.print(current_position[Y_AXIS]);
    // Serial.print(",");
    // Serial.println(current_position[Z_AXIS]);
    // Serial.println("________________________");

    /** START PRINTING **/
    if (!is_segment_printing_)
    {
        is_segment_printing_ = true;
    }

    if (current_position[X_AXIS] != target_position[X_AXIS] ||
        current_position[Y_AXIS] != target_position[Y_AXIS] ||
        current_position[Z_AXIS] != target_position[Z_AXIS])
    {

        for (int i = 0; i < N_AXIS; ++i)
        {
            if (current_position[i] != target_position[i])
            {
                axis_[i].move_step(axis_[i].get_direction());
            }
        }
    }
    else
    {
        /** END PRINTING **/
        is_segment_printing_ = false;
        Serial.println("Finished segment!");
    }
}

void Planner::load_drawing(double drawing_to_plot[][N_AXIS], int drawing_size)
{

    Serial.println("Start printing!");
    finished_drawing_ = false;
    current_drawing_ = drawing_to_plot;
    current_drawing_size_ = drawing_size;
}

// void Planner::plot_drawing()
// {
//     if (!finished_drawing_)
//     {
//         if (!is_segment_printing_ && current_segment_ < current_drawing_size_)
//         {
//             // Converting current target position into steps
//             // this is a local variable, it may be flushed after a while?
//             const int target_to_steps[N_AXIS] = {
//                 int(mm_to_steps(X_STEPS_PER_MM, current_drawing_[current_segment_][X_AXIS])),
//                 int(mm_to_steps(Y_STEPS_PER_MM, current_drawing_[current_segment_][Y_AXIS])),
//                 int(mm_to_steps(Z_STEPS_PER_MM, current_drawing_[current_segment_][Z_AXIS]))};

//             // start of segment
//             // init_segment_plan(drawing_to_plot[current_segment_]);
//             init_segment_plan(target_to_steps);
//             // print_segment_positions();
//             // print_segment();
//             move_to_position();
//             Serial.print("Finished segment: ");
//             Serial.println(current_segment_);
//             print_stepper();
//             current_segment_++;
//         }
//         else if (is_segment_printing_)
//         {
//             move_to_position();
//         }
//         else if (current_segment_ == current_drawing_size_)
//         {
//             print_stepper();
//             Serial.println("Finished drawing!");
//             current_drawing_ = nullptr;
//             current_drawing_size_ = 0;
//             current_segment_ = 0;
//             finished_drawing_ = true;
//             is_segment_printing_ = false;
//         }
//     }
// }

bool Planner::is_drawing_finished()
{
    return finished_drawing_;
}