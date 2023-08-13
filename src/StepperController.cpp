#include "StepperController.h"

StepperController::StepperController() : step_pin{X_STEP_PIN, Y_STEP_PIN, Z_STEP_PIN},
                                         dir_pin{X_DIR_PIN, Y_DIR_PIN, Z_DIR_PIN}, steps_counter{0, 0, 0}
{
  // Initializing values
  en_pin = EN_PIN;
  pulse_time_stamp_ = micros();
  move_time_stamp_ = micros();
  steps_rate_ = STEPS_RATE;

  // Declare pins as Outputs
  pinMode(step_pin[X_AXIS], OUTPUT);
  pinMode(dir_pin[X_AXIS], OUTPUT);
  pinMode(step_pin[Y_AXIS], OUTPUT);
  pinMode(dir_pin[Y_AXIS], OUTPUT);
  pinMode(step_pin[Z_AXIS], OUTPUT);
  pinMode(dir_pin[Z_AXIS], OUTPUT);
  pinMode(en_pin, OUTPUT);
  this->setEnable(false);
}

/*    SETTERS    **/
void StepperController::setStepsRate(unsigned long steps_rate)
{
  if (steps_rate >= 0)
  {
    steps_rate_ = steps_rate;
  }
}

void StepperController::setEnable(bool isEnabled)
{
  digitalWrite(EN_PIN, !isEnabled);
}

void StepperController::setDirection(int current_direction_mask)
{
  // set by the digit bits - if a bit is turned on, flip direction
  current_direction_mask = current_direction_mask ^ DIRECTION_INVERT_MASK;
  digitalWrite(dir_pin[X_AXIS], bit_istrue(current_direction_mask, 1 << X_AXIS));
  digitalWrite(dir_pin[Y_AXIS], bit_istrue(current_direction_mask, 1 << Y_AXIS));
  digitalWrite(dir_pin[Z_AXIS], bit_istrue(current_direction_mask, 1 << Z_AXIS));
}

void StepperController::setStepsCount(int x_steps, int y_steps, int z_steps)
{
  steps_counter[X_AXIS] = x_steps;
  steps_counter[Y_AXIS] = y_steps;
  steps_counter[Z_AXIS] = z_steps;
}

/*    GETTERS    **/
const int *StepperController::getStepsCount() const
{
  return steps_counter;
}

/*    MOVEMENT METHODS    **/
void StepperController::moveStep(int current_step_mask, int current_direction_mask)
{
  unsigned long currnet_time_stamp = micros();
  // start of pulse
  if (pulse_time_stamp_ == 0)
  {
    pulse_time_stamp_ = micros();
    digitalWrite(step_pin[X_AXIS], bit_istrue(current_step_mask, 1 << X_AXIS));
    digitalWrite(step_pin[Y_AXIS], bit_istrue(current_step_mask, 1 << Y_AXIS));
    digitalWrite(step_pin[Z_AXIS], bit_istrue(current_step_mask, 1 << Z_AXIS));
    // count motors steps
    // need to flip when direction bit is on
    steps_counter[X_AXIS] += bit_to_sign(current_direction_mask, 1 << X_AXIS) * bit_istrue(current_step_mask, 1 << X_AXIS);
    steps_counter[Y_AXIS] += bit_to_sign(current_direction_mask, 1 << Y_AXIS) * bit_istrue(current_step_mask, 1 << Y_AXIS);
    steps_counter[Z_AXIS] += bit_to_sign(current_direction_mask, 1 << Z_AXIS) * bit_istrue(current_step_mask, 1 << Z_AXIS);
  }
  // end pulse
  // in case that the pulse time was ended OR in case that the micros value was overflowed complete the pulse
  if (currnet_time_stamp - pulse_time_stamp_ > STEP_PULSE_LENGTH || currnet_time_stamp < pulse_time_stamp_)
  {
    digitalWrite(step_pin[X_AXIS], LOW);
    digitalWrite(step_pin[Y_AXIS], LOW);
    digitalWrite(step_pin[Z_AXIS], LOW);
    pulse_time_stamp_ = 0;
  }
}

void StepperController::move_(int steps_mask, int current_direction_mask)
{
  unsigned long currnet_time_stamp = micros();
  // start of movement
  if (steps_mask != 0 && move_time_stamp_ == 0)
  {
    move_time_stamp_ = micros();
  }
  else if (move_time_stamp_ != 0 && currnet_time_stamp - move_time_stamp_ > steps_rate_)
  {
    //          || currnet_time_stamp < _stepper_config -> move_time_stamp
    this->setDirection(current_direction_mask);
    this->moveStep(steps_mask, current_direction_mask);
    move_time_stamp_ = 0;

    // case that pulse ended - reset time stamp
    //          if (digitalRead(_stepper_config->step_pin) != HIGH){
    //            _stepper_config->move_time_stamp = 0;
    //            }
  }
}

int StepperController::getLineDirectionMask(const int *point1, const int *point2)
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
