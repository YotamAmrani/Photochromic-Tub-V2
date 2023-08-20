#include "StepperController.h"

StepperController::StepperController() : step_pin_{X_STEP_PIN, Y_STEP_PIN, Z_STEP_PIN},
                                         dir_pin_{X_DIR_PIN, Y_DIR_PIN, Z_DIR_PIN}, en_pin_(EN_PIN), steps_counter_{0, 0, 0}
{
  // Initializing values
  move_time_stamp_ = micros();
  steps_rate_ = STEPS_RATE;

  // Declare pins as Outputs
  pinMode(step_pin_[X_AXIS], OUTPUT);
  pinMode(dir_pin_[X_AXIS], OUTPUT);
  pinMode(step_pin_[Y_AXIS], OUTPUT);
  pinMode(dir_pin_[Y_AXIS], OUTPUT);
  pinMode(step_pin_[Z_AXIS], OUTPUT);
  pinMode(dir_pin_[Z_AXIS], OUTPUT);
  pinMode(en_pin_, OUTPUT);
  this->set_enable(false);
}

/*    SETTERS    **/
void StepperController::set_steps_rate(unsigned long steps_rate)
{
  if (steps_rate >= 0)
  {
    steps_rate_ = steps_rate;
  }
}

void StepperController::set_enable(bool isEnabled)
{
  digitalWrite(EN_PIN, !isEnabled);
}

void StepperController::set_direction(int current_direction_mask)
{
  // set by the digit bits - if a bit is turned on, flip direction
  current_direction_mask = current_direction_mask ^ DIRECTION_INVERT_MASK;
  digitalWrite(dir_pin_[X_AXIS], bit_istrue(current_direction_mask, 1 << X_AXIS));
  digitalWrite(dir_pin_[Y_AXIS], bit_istrue(current_direction_mask, 1 << Y_AXIS));
  digitalWrite(dir_pin_[Z_AXIS], bit_istrue(current_direction_mask, 1 << Z_AXIS));
}

void StepperController::set_steps_count(int x_steps, int y_steps, int z_steps)
{
  steps_counter_[X_AXIS] = x_steps;
  steps_counter_[Y_AXIS] = y_steps;
  steps_counter_[Z_AXIS] = z_steps;
}

/*    GETTERS    **/
const int *StepperController::get_steps_count() const
{
  return steps_counter_;
}

/*    MOVEMENT METHODS    **/
void StepperController::step(int current_step_mask, int current_direction_mask)
{
  // start of pulse
  digitalWrite(step_pin_[X_AXIS], bit_istrue(current_step_mask, 1 << X_AXIS));
  digitalWrite(step_pin_[Y_AXIS], bit_istrue(current_step_mask, 1 << Y_AXIS));
  digitalWrite(step_pin_[Z_AXIS], bit_istrue(current_step_mask, 1 << Z_AXIS));
  // count motors steps, flip when direction bit is on
  steps_counter_[X_AXIS] += bit_to_sign(current_direction_mask, 1 << X_AXIS) * bit_istrue(current_step_mask, 1 << X_AXIS);
  steps_counter_[Y_AXIS] += bit_to_sign(current_direction_mask, 1 << Y_AXIS) * bit_istrue(current_step_mask, 1 << Y_AXIS);
  steps_counter_[Z_AXIS] += bit_to_sign(current_direction_mask, 1 << Z_AXIS) * bit_istrue(current_step_mask, 1 << Z_AXIS);
  delayMicroseconds(STEP_PULSE_LENGTH);
  // end pulse
  digitalWrite(step_pin_[X_AXIS], LOW);
  digitalWrite(step_pin_[Y_AXIS], LOW);
  digitalWrite(step_pin_[Z_AXIS], LOW);
}

void StepperController::move_step(int steps_mask, int current_direction_mask)
{
  // turn sed pulse
  if (steps_mask && (micros() - move_time_stamp_ > steps_rate_))
  {

    this->step(steps_mask, current_direction_mask); // Send step

    move_time_stamp_ = micros(); // reset timer
  }
  // if (move_time_stamp_ && (micros() - move_time_stamp_ > steps_rate_))
  // {
  //   this->step(steps_mask, current_direction_mask); // Send step
  //   move_time_stamp_ = 0;                           // reset timer
  //   // Serial.println(move_time_stamp_);
  // }
  // if (!move_time_stamp_ && steps_mask)
  // {
  //   move_time_stamp_ = micros();
  //   // Serial.println(move_time_stamp_);
  // }
  // if (steps_mask == 0 && move_time_stamp_)
  // {
  //   Serial.println("F");
  // }
  // if (steps_mask == 0 && move_time_stamp_ == 0)
  // {
  //   // Serial.println("A");
  //   move_time_stamp_ = micros();
  // }
  // if (steps_mask != 0 && move_time_stamp_)
  // {
  //   Serial.println("B");
  // }
  // if (steps_mask != 0 && move_time_stamp_ == 0)
  // {
  //   Serial.println("C");
  // }
  // In this state A does not appear, if i'll remove the upper condition (&& steps_mask)
  //  from the first if, it will appear - and we are getting locked!
  //  C does not appear in all cases
}

// void StepperController::move_step(int steps_mask, int current_direction_mask)
// {
//   unsigned long currnet_time_stamp = micros();
//   // start of movement
//   if (steps_mask != 0 && move_time_stamp_ == 0)
//   {
//     move_time_stamp_ = micros();
//   }
//   else if (move_time_stamp_ != 0 && currnet_time_stamp - move_time_stamp_ > steps_rate_)
//   {
//     // TODO: changing the (steps_mask != 0) condition to (move_time_stamp_ != 0)
//     //          || currnet_time_stamp < _stepper_config -> move_time_stamp
//     this->set_direction(current_direction_mask);
//     this->step(steps_mask, current_direction_mask);
//     if (move_time_stamp_ == 0)
//     {
//       Serial.println(move_time_stamp_);
//     }
//     move_time_stamp_ = 0;
//     // case that pulse ended - reset time stamp
//     //          if (digitalRead(_stepper_config->step_pin_) != HIGH){
//     //            _stepper_config->move_time_stamp = 0;
//     //            }
//   }
// }