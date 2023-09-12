#include "StepperController.h"

StepperController::StepperController() : step_pin_{X_STEP_PIN, Y_STEP_PIN, Z_STEP_PIN},
                                         dir_pin_{X_DIR_PIN, Y_DIR_PIN, Z_DIR_PIN},
                                         led_pin_(LED_PIN),
                                         en_pin_(EN_PIN), steps_counter_{0, 0, 0},
                                         max_steps_{mm_to_steps(X_MM_LIMIT, X_STEPS_PER_MM), mm_to_steps(Y_MM_LIMIT, Y_STEPS_PER_MM), mm_to_steps(Z_MM_LIMIT, Z_STEPS_PER_MM)},
                                         led_pwm_value_(0)

{
  // Initializing values
  move_time_stamp_ = micros();
  steps_counter_[X_AXIS] = max_steps_[X_AXIS];
  steps_counter_[Y_AXIS] = max_steps_[Y_AXIS];
  steps_counter_[Z_AXIS] = max_steps_[Z_AXIS];
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

void StepperController::set_led_value(int led_pwm_value)
{
  led_pwm_value_ = led_pwm_value;
  analogWrite(LED_PIN, led_pwm_value);
}

/*    GETTERS    **/
const int *StepperController::get_steps_count() const
{
  return steps_counter_;
}

/*    MOVEMENT METHODS    **/
void StepperController::step(int current_step_mask, int current_direction_mask)
{
#ifdef ENABLE_SOFT_LIMIT
  for (int i = 0; i < N_AXIS; ++i)
  {
    int current_step = bit_to_sign(current_direction_mask, 1 << i) * bit_istrue(current_step_mask, 1 << i);

    if (current_step + steps_counter_[i] <= max_steps_[i] && current_step + steps_counter_[i] >= 0)
    {
      digitalWrite(step_pin_[i], bit_istrue(current_step_mask, 1 << i));
      steps_counter_[i] += bit_to_sign(current_direction_mask, 1 << i) * bit_istrue(current_step_mask, 1 << i);
    }
    // if (steps_counter_[i] + 100 > max_steps_[i])
    // {
    //   steps_rate_ = steps_rate_ * (100 - (max_steps_[i] - steps_counter_[i]) + 1);
    // }
  }

#else
  // start of pulse
  digitalWrite(step_pin_[X_AXIS], bit_istrue(current_step_mask, 1 << X_AXIS));
  digitalWrite(step_pin_[Y_AXIS], bit_istrue(current_step_mask, 1 << Y_AXIS));
  digitalWrite(step_pin_[Z_AXIS], bit_istrue(current_step_mask, 1 << Z_AXIS));
  // count motors steps, flip when direction bit is on
  steps_counter_[X_AXIS] += bit_to_sign(current_direction_mask, 1 << X_AXIS) * bit_istrue(current_step_mask, 1 << X_AXIS);
  steps_counter_[Y_AXIS] += bit_to_sign(current_direction_mask, 1 << Y_AXIS) * bit_istrue(current_step_mask, 1 << Y_AXIS);
  steps_counter_[Z_AXIS] += bit_to_sign(current_direction_mask, 1 << Z_AXIS) * bit_istrue(current_step_mask, 1 << Z_AXIS);

#endif
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
    set_direction(current_direction_mask);
    this->step(steps_mask, current_direction_mask); // Send step
    move_time_stamp_ = micros();                    // reset timer
  }
}
