#include "Planner.h"
#include <Arduino.h>

Planner::Planner(StepperController *stepper_c, struct segment_plan *seg_pl)
{
    _stepper_c = stepper_c;
    _segment_plan = seg_pl;
    current_drawing = nullptr;
    current_segment = 0;
    is_printing = false;
    finished_drawing = true;
}

void Planner::printStepper()
{
    const int *pos = _stepper_c->getStepsCount();
    Serial.println("POS:");
    Serial.print(pos[X_AXIS]);
    Serial.print(",");
    Serial.print(pos[Y_AXIS]);
    Serial.print(",");
    Serial.println(pos[Z_AXIS]);
}

void Planner::initSegmentPlan(const int *target_pos)
{
    _segment_plan->current_position = _stepper_c->getStepsCount();
    _segment_plan->target_position = target_pos;
    _segment_plan->dx = abs(_segment_plan->current_position[X_AXIS] - target_pos[X_AXIS]);
    _segment_plan->dy = abs(_segment_plan->current_position[Y_AXIS] - target_pos[Y_AXIS]);
    _segment_plan->dz = abs(_segment_plan->current_position[Z_AXIS] - target_pos[Z_AXIS]);
    _segment_plan->dominant_axis = max(max(_segment_plan->dx, _segment_plan->dy), _segment_plan->dz);
    _segment_plan->x_step_value = 0;
    _segment_plan->y_step_value = 0;
    _segment_plan->z_step_value = 0;
    // Set steps directions
    _segment_plan->current_direction_mask = getLineDirectionMask(_segment_plan->current_position, _segment_plan->target_position);
    _segment_plan->current_step_mask = 0;
    // _segment_plan->segment_is_enabled = false;
}

void Planner::moveToPosition()
{

    if (_segment_plan->current_position[X_AXIS] != _segment_plan->target_position[X_AXIS] || _segment_plan->current_position[Y_AXIS] != _segment_plan->target_position[Y_AXIS] || _segment_plan->current_position[Z_AXIS] != _segment_plan->target_position[Z_AXIS])
    {
        if (!is_printing)
        {
            is_printing = true;
            _stepper_c->setEnable(true);
            _stepper_c->setDirection(_segment_plan->current_direction_mask);
        }
        _segment_plan->current_step_mask = 0;
        if (_segment_plan->dx && (_segment_plan->x_step_value >= _segment_plan->dominant_axis))
        {
            _segment_plan->current_step_mask = _segment_plan->current_step_mask | (1 << X_AXIS);
            _segment_plan->x_step_value -= _segment_plan->dominant_axis;
        }
        if (_segment_plan->dy && (_segment_plan->y_step_value >= _segment_plan->dominant_axis))
        {
            _segment_plan->current_step_mask = _segment_plan->current_step_mask | (1 << Y_AXIS);
            _segment_plan->y_step_value -= _segment_plan->dominant_axis;
        }
        if (_segment_plan->dz && (_segment_plan->z_step_value >= _segment_plan->dominant_axis))
        {
            _segment_plan->current_step_mask = _segment_plan->current_step_mask | (1 << Z_AXIS);
            _segment_plan->z_step_value -= _segment_plan->dominant_axis;
        }

        _segment_plan->x_step_value += _segment_plan->dx;
        _segment_plan->y_step_value += _segment_plan->dy;
        _segment_plan->z_step_value += _segment_plan->dz;

        _stepper_c->move_(_segment_plan->current_step_mask, _segment_plan->current_direction_mask);
    }
    else
    {
        _stepper_c->setEnable(false);
        is_printing = false;
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
    current_drawing = (int **)drawing_to_plot;
}

void Planner::plotDrawing(int drawing_to_plot[][N_AXIS], int array_size)
{
    if (!finished_drawing)
    {
        if (!is_printing && current_segment < array_size)
        {
            // start of segment
            initSegmentPlan(drawing_to_plot[current_segment]);
            moveToPosition();
            Serial.print("Finished segment:");
            Serial.println(current_segment);
            current_segment++;
        }
        else if (is_printing)
        {
            moveToPosition();
        }
        else if (current_segment == array_size)
        {
            Serial.println("Finished drawing!");
            current_drawing = nullptr;
            current_segment = 0;
            finished_drawing = true;
            is_printing = false;
        }
    }

    // // case init drawing
    // if (current_segment == 0)
    // {
    //     current_drawing = drawing_to_plot;
    //     initSegmentPlan(drawing_to_plot[current_segment]);
    //     is_printing = true;
    // }
    // else if (is_printing && current_segment < array_size)
    // {
    //     // keep moving, until reaching the end of the array
    //     moveToPosition();
    // }

    // else if (!is_printing && current_segment < array_size)
    // {
    //     current_segment++;
    //     initSegmentPlan(drawing_to_plot[current_segment]);
    // }
    // else if (current_segment == array_size)
    // {
    //     current_segment == 0;
    //     Serial.print("Finished drawing!");
    // }
    // case finished drawing
}