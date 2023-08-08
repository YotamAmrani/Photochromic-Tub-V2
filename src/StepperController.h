
#ifndef STEPPER_CONTROLLER_H
#include <Arduino.h>
#include "Settings.h"
#define STEPPER_CONTROLLER_H

struct stepper_config
{
  const int axis[N_AXIS];
  const int step_pin[N_AXIS];
  const int dir_pin[N_AXIS];
  const int en_pin;
  unsigned long pulse_time_stamp;
  unsigned long move_time_stamp;
  unsigned long steps_rate;
  int steps_counter[N_AXIS];
};

struct step_plan
{
  unsigned long steps_rate;
  int steps_mask;
  int direction_mask;
  bool led_state;
};

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
  bool segment_is_enabled;
};

class StepperController
{
private:
  struct stepper_config *_stepper_config;
  struct move_prop *_move_prop;

  void moveStep(int current_step_mask, int current_direction_mask);

  int getLineDirectionMask(const int *point1, const int *point2);

public:
  StepperController(struct stepper_config *stepper_config);

  void setDirection(int current_direction_mask);

  void setStepsRate(unsigned long steps_rate);

  void setEnable(bool isEnabled);

  void move_(int steps_mask, int current_direction_mask);

  const int *getStepsCount() const;
  // https://stackoverflow.com/questions/10716769/c-difference-between-const-positioning

  void setStepsCount(int x_steps, int y_steps, int z_steps);

  void moveToPosition(const int *point);

  void moveToPosition(struct segment_plan *seg_p);

  void initSegmentPlan(struct segment_plan *seg_p, const int *target_position);
};

#endif