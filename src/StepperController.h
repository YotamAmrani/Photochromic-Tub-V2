
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
  int get_line_direction_mask(const int *point1, const int *point2);

public:
  StepperController();

  void set_direction(int current_direction_mask);

  void set_steps_rate(unsigned long steps_rate);

  void set_enable(bool isEnabled);

  void move_step(int steps_mask, int current_direction_mask);

  const int *get_steps_count() const;
  // https://stackoverflow.com/questions/10716769/c-difference-between-const-positioning

  void set_steps_count(int x_steps, int y_steps, int z_steps);
};

#endif
