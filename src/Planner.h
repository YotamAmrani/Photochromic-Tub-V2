#ifndef PLANNER_H
#define PLANNER_H
#include "Stepper.h"

/** segment -represents the current line to plot **/
struct segment_plan
{
    int target_position[N_AXIS];
    int current_step_mask[N_AXIS];
    int dominant_axis;
};

/** A Planner for handling line plotting in a Non-Blocking manner **/
class Planner
{
private:
    Stepper *axis_;
    double (*current_drawing_)[N_AXIS];
    // https://stackoverflow.com/questions/22975633/reference-to-a-static-2d-array
    int current_drawing_size_;
    int current_segment_;
    bool finished_drawing_;

public:
    bool is_segment_printing_;
    Planner(Stepper (&axis)[N_AXIS]);
    // void print_stepper();
    // void print_segment();
    // void print_steps();
    // void print_segment_positions();
    void init_segment_plan(const int *target_pos);
    void load_drawing(double drawing_to_plot[][N_AXIS], int drawing_size);
    void move_to_position(const int *target_pos);
    // int get_line_direction_mask(const int *point1, const int *point2);
    // void plot_drawing();
    bool is_drawing_finished();
};

#endif
