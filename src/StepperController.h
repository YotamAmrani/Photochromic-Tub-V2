
#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H
#include <Arduino.h>
#include "Settings.h"

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
  const int step_pin_[N_AXIS];
  const int dir_pin_[N_AXIS];
  const int led_pin_;
  const int en_pin_;
  unsigned long move_time_stamp_;
  unsigned long steps_rate_;
  unsigned long steps_counter_[N_AXIS];
  const unsigned long max_steps_[N_AXIS];
  int led_pwm_value_;

  void step(int current_step_mask, int current_direction_mask);

public:
  /**
   * Stepper Controller constructor.
   */
  StepperController();

  /**
   * Setting the steppers directions based on the given direction mask.
   *
   * @param current_direction_mask - direction mask (integer representation)
   */
  void set_direction(int current_direction_mask);

  /**
   * Setting the steppers steps rate (i.e. the interval between one step to another)
   *
   * @param steps_rate the time interval (in microseconds) between two consequtive steps.
   */
  void set_steps_rate(unsigned long steps_rate);

  /**
   * Set all steppers in enable/disable mode.
   *
   * @param isEnabled - True to enable, false to disable.
   */
  void set_enable(bool isEnabled);

  /**
   * Set The led PWM value (in the range of 0 to 255)
   *
   * @param led_pwm_value - PWM value
   */
  void set_led_value(int led_pwm_value);

  /**
   * Moving the system one step according to the current movement and direction masks.
   * for each motor, their is a designated bit on the direction mask, and a designated bit
   * on the movement mask.
   *
   * In case that the movement bit is turned on - the motor should preform a step.
   * In case that the direction bit is turned on, the motor should move to the negative direction.
   * (otherwise, it will move to the posotive direction)
   *
   * @param steps_mask - The steps movement mask
   * @param current_direction_mask - The motors direction mask
   */
  void move_step(int steps_mask, int current_direction_mask);

  /**
   * Returns the current steps count (i.e. the position of each axis in steps)
   * @return a pointer to steps_counter_ an array of 3 counter, one per each axis X, Y, Z in order.
   */
  const unsigned long *get_steps_count() const;
  // https://stackoverflow.com/questions/10716769/c-difference-between-const-positioning

  /**
   * Set the current steps count to given values. (used mainly for auto-homing phase)
   *
   * @param x_steps value to set on x axis
   * @param y_steps value to set on y axis
   * @param z_steps value to set on z axis
   */
  void set_steps_count(unsigned long x_steps, unsigned long y_steps, unsigned long z_steps);
};

#endif
