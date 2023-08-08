#ifndef PLANNER_H
#define PLANNER_H
#include "StepperController.h"

/** A Planner for handling line plotting in a Non-Blocking manner **/

class Planner
{
private:
    StepperController *_stepper_c;
    struct segment_plan *_segment_plan;

public:
    Planner(StepperController *stepperC, struct segment_plan *seg_pl);
    void printStepper();
    void initSegmentPlan(const int *target_pos);
    // void Planner::moveToPosition(const int *next_position);
    void moveToPosition(struct segment_plan *seg_p);
    int getLineDirectionMask(const int *point1, const int *point2);
};

#endif
