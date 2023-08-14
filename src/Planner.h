#ifndef PLANNER_H
#define PLANNER_H
#include "StepperController.h"

/** segment -represents the current line to plot **/
struct segment_plan
{
    const int *current_position;
    const int *target_position;
    int current_step_mask;
    int current_direction_mask;
    int dx;
    int dy;
    int dz;
    int dominant_axis;
    int x_step_value;
    int y_step_value;
    int z_step_value;
};

/** A Planner for handling line plotting in a Non-Blocking manner **/
class Planner
{
private:
    StepperController *stepper_c_;
    struct segment_plan *segment_plan_;
    int **current_drawing_;
    int current_segment_;
    bool is_printing_;
    bool finished_drawing_;

public:
    Planner(StepperController *stepper_c, struct segment_plan *seg_pl);
    void print_stepper();
    void init_segment_plan(const int *target_pos);
    void load_drawing(int drawing_to_plot[][N_AXIS]);
    void move_to_position();
    int get_line_direction_mask(const int *point1, const int *point2);
    void plotDrawing(int drawing_to_plot[][N_AXIS], int array_size);
};

#endif
