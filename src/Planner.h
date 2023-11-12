#ifndef PLANNER_H
#define PLANNER_H
#include "StepperController.h"
#include "Drawings.h"

/** segment -represents the current line to plot **/
struct segment_plan
{
    const unsigned long *current_position;
    unsigned long target_position[N_AXIS];
    int current_step_mask;
    int current_direction_mask;
    int dx;
    int dy;
    int dz;
    int dominant_axis;
    int x_step_value;
    int y_step_value;
    int z_step_value;
    int led_pwm_value;
};

/** A Planner for handling line plotting in a Non-Blocking manner **/
class Planner
{
private:
    StepperController *stepper_c_;
    Drawing *current_drawing_;
    struct segment_plan *segment_plan_;
    // double (*current_drawing_)[N_AXIS];
    // https://stackoverflow.com/questions/22975633/reference-to-a-static-2d-array
    int current_segment_;
    bool finished_drawing_;

public:
    bool is_segment_printing_;
    Planner(StepperController *stepper_c, struct segment_plan *seg_pl);
    void print_stepper();
    void print_segment();
    void print_steps();
    void print_segment_positions();
    void test_print();
    void init_segment_plan(const int *target_pos);
    // void load_drawing(double drawing_to_plot[][N_AXIS], int drawing_size);
    // void load_drawing(int drawingId, Drawing drawings[]);
    void load_drawing(Drawing *current_drawing);
    void move_to_position();
    int get_line_direction_mask(const unsigned long *point1, const unsigned long *point2);
    void plot_drawing();
    bool is_drawing_finished();
    void reset_drawing();
};

#endif
