#include "Planner.h"
#include <Arduino.h>

Planner::Planner(StepperController *stepper_c, struct segment_plan *seg_pl)
{
    stepper_c_ = stepper_c;
    segment_plan_ = seg_pl;
    current_drawing_ = nullptr;
    current_segment_ = 0;
    is_printing_ = false;
    finished_drawing = true;
}

void Planner::printStepper()
{
    const int *pos = stepper_c_->getStepsCount();
    Serial.println("POS:");
    Serial.print(pos[X_AXIS]);
    Serial.print(",");
    Serial.print(pos[Y_AXIS]);
    Serial.print(",");
    Serial.println(pos[Z_AXIS]);
}

void Planner::initSegmentPlan(const int *target_pos)
{
    segment_plan_->current_position = stepper_c_->getStepsCount();
    segment_plan_->target_position = target_pos;
    segment_plan_->dx = abs(segment_plan_->current_position[X_AXIS] - target_pos[X_AXIS]);
    segment_plan_->dy = abs(segment_plan_->current_position[Y_AXIS] - target_pos[Y_AXIS]);
    segment_plan_->dz = abs(segment_plan_->current_position[Z_AXIS] - target_pos[Z_AXIS]);
    segment_plan_->dominant_axis = max(max(segment_plan_->dx, segment_plan_->dy), segment_plan_->dz);
    segment_plan_->x_step_value = 0;
    segment_plan_->y_step_value = 0;
    segment_plan_->z_step_value = 0;
    // Set steps directions
    segment_plan_->current_direction_mask = getLineDirectionMask(segment_plan_->current_position, segment_plan_->target_position);
    segment_plan_->current_step_mask = 0;
    // _segment_plan->segment_is_enabled = false;
}

void Planner::moveToPosition()
{

    if (segment_plan_->current_position[X_AXIS] != segment_plan_->target_position[X_AXIS] || segment_plan_->current_position[Y_AXIS] != segment_plan_->target_position[Y_AXIS] || segment_plan_->current_position[Z_AXIS] != segment_plan_->target_position[Z_AXIS])
    {
        if (!is_printing_)
        {
            is_printing_ = true;
            stepper_c_->setEnable(true);
            stepper_c_->setDirection(segment_plan_->current_direction_mask);
        }
        segment_plan_->current_step_mask = 0;
        if (segment_plan_->dx && (segment_plan_->x_step_value >= segment_plan_->dominant_axis))
        {
            segment_plan_->current_step_mask = segment_plan_->current_step_mask | (1 << X_AXIS);
            segment_plan_->x_step_value -= segment_plan_->dominant_axis;
        }
        if (segment_plan_->dy && (segment_plan_->y_step_value >= segment_plan_->dominant_axis))
        {
            segment_plan_->current_step_mask = segment_plan_->current_step_mask | (1 << Y_AXIS);
            segment_plan_->y_step_value -= segment_plan_->dominant_axis;
        }
        if (segment_plan_->dz && (segment_plan_->z_step_value >= segment_plan_->dominant_axis))
        {
            segment_plan_->current_step_mask = segment_plan_->current_step_mask | (1 << Z_AXIS);
            segment_plan_->z_step_value -= segment_plan_->dominant_axis;
        }

        segment_plan_->x_step_value += segment_plan_->dx;
        segment_plan_->y_step_value += segment_plan_->dy;
        segment_plan_->z_step_value += segment_plan_->dz;

        stepper_c_->moveStep(segment_plan_->current_step_mask, segment_plan_->current_direction_mask);
    }
    else
    {
        stepper_c_->setEnable(false);
        is_printing_ = false;
    }
}

int Planner::getLineDirectionMask(const int *point1, const int *point2)
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

void Planner::loadDrawing(int drawing_to_plot[][N_AXIS])
{
    Serial.println("Start printing!");
    finished_drawing = false;
    current_drawing_ = (int **)drawing_to_plot;
}

void Planner::plotDrawing(int drawing_to_plot[][N_AXIS], int array_size)
{
    if (!finished_drawing)
    {
        if (!is_printing_ && current_segment_ < array_size)
        {
            // start of segment
            initSegmentPlan(drawing_to_plot[current_segment_]);
            moveToPosition();
            Serial.print("Finished segment:");
            Serial.println(current_segment_);
            current_segment_++;
        }
        else if (is_printing_)
        {
            moveToPosition();
        }
        else if (current_segment_ == array_size)
        {
            Serial.println("Finished drawing!");
            current_drawing_ = nullptr;
            current_segment_ = 0;
            finished_drawing = true;
            is_printing_ = false;
        }
    }
}