#ifndef PLANNER_H
#define PLANNER_H
#include "StepperController.h"

/** A Planner for handling line plotting in a Non-Blocking manner **/

class Planner
{
private:
    StepperController *_stepper_c;
    struct segment_plan *_segment_plan;
    int **current_drawing;
    int current_segment;
    bool is_printing;
    bool finished_drawing;

public:
    Planner(StepperController *stepperC, struct segment_plan *seg_pl);
    void printStepper();
    void initSegmentPlan(const int *target_pos);
    void loadDrawing(int drawing_to_plot[][N_AXIS]);
    void moveToPosition();
    int getLineDirectionMask(const int *point1, const int *point2);
    void plotDrawing(int drawing_to_plot[][N_AXIS], int array_size);
};

#endif
