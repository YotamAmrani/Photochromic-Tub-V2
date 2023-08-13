
#ifndef STEPPER_CONTROLLER_H
#include <Arduino.h>
#include "Settings.h"
#define STEPPER_CONTROLLER_H

struct step_plan
{
  unsigned long steps_rate;
  int steps_mask;
  int direction_mask;
  bool led_state;
};

class StepperController
{
private:
  // struct stepper_config *_stepper_config;
  const int step_pin_[N_AXIS];
  const int dir_pin_[N_AXIS];
  const int en_pin_;
  unsigned long pulse_time_stamp_;
  unsigned long move_time_stamp_;
  unsigned long steps_rate_;
  int steps_counter_[N_AXIS];

  void step(int current_step_mask, int current_direction_mask);
  int getLineDirectionMask(const int *point1, const int *point2);

public:
  StepperController();

  void setDirection(int current_direction_mask);

  void setStepsRate(unsigned long steps_rate);

  void setEnable(bool isEnabled);

  void moveStep(int steps_mask, int current_direction_mask);

  const int *getStepsCount() const;
  // https://stackoverflow.com/questions/10716769/c-difference-between-const-positioning

  void setStepsCount(int x_steps, int y_steps, int z_steps);
};

#endif
