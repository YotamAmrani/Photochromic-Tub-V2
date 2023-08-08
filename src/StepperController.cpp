#include "StepperController.h"

StepperController::StepperController(struct stepper_config *stepper_config)
{
  _stepper_config = stepper_config;

  // Declare pins as Outputs
  pinMode(_stepper_config->step_pin[X_AXIS], OUTPUT);
  pinMode(_stepper_config->dir_pin[X_AXIS], OUTPUT);
  pinMode(_stepper_config->step_pin[Y_AXIS], OUTPUT);
  pinMode(_stepper_config->dir_pin[Y_AXIS], OUTPUT);
  pinMode(_stepper_config->step_pin[Z_AXIS], OUTPUT);
  pinMode(_stepper_config->dir_pin[Z_AXIS], OUTPUT);
  pinMode(_stepper_config->en_pin, OUTPUT);
  this->setEnable(false);
}

/*    SETTERS    **/
void StepperController::setStepsRate(unsigned long steps_rate)
{
  if (steps_rate >= 0)
  {
    _stepper_config->steps_rate = steps_rate;
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
  digitalWrite(_stepper_config->dir_pin[X_AXIS], bit_istrue(current_direction_mask, 1 << X_AXIS));
  digitalWrite(_stepper_config->dir_pin[Y_AXIS], bit_istrue(current_direction_mask, 1 << Y_AXIS));
  digitalWrite(_stepper_config->dir_pin[Z_AXIS], bit_istrue(current_direction_mask, 1 << Z_AXIS));
}

void StepperController::setStepsCount(int x_steps, int y_steps, int z_steps)
{
  _stepper_config->steps_counter[X_AXIS] = x_steps;
  _stepper_config->steps_counter[Y_AXIS] = y_steps;
  _stepper_config->steps_counter[Z_AXIS] = z_steps;
}

/*    GETTERS    **/
const int *StepperController::getStepsCount() const
{
  return _stepper_config->steps_counter;
}

/*    MOVEMENT METHODS    **/
void StepperController::moveStep(int current_step_mask, int current_direction_mask)
{
  unsigned long currnet_time_stamp = micros();
  // start of pulse
  if (_stepper_config->pulse_time_stamp == 0)
  {
    _stepper_config->pulse_time_stamp = micros();
    digitalWrite(_stepper_config->step_pin[X_AXIS], bit_istrue(current_step_mask, 1 << X_AXIS));
    digitalWrite(_stepper_config->step_pin[Y_AXIS], bit_istrue(current_step_mask, 1 << Y_AXIS));
    digitalWrite(_stepper_config->step_pin[Z_AXIS], bit_istrue(current_step_mask, 1 << Z_AXIS));
    // count motors steps
    // need to flip when direction bit is on
    _stepper_config->steps_counter[X_AXIS] += bit_to_sign(current_direction_mask, 1 << X_AXIS) * bit_istrue(current_step_mask, 1 << X_AXIS);
    _stepper_config->steps_counter[Y_AXIS] += bit_to_sign(current_direction_mask, 1 << Y_AXIS) * bit_istrue(current_step_mask, 1 << Y_AXIS);
    _stepper_config->steps_counter[Z_AXIS] += bit_to_sign(current_direction_mask, 1 << Z_AXIS) * bit_istrue(current_step_mask, 1 << Z_AXIS);
  }
  // end pulse
  // in case that the pulse time was ended OR in case that the micros value was overflowed complete the pulse
  if (currnet_time_stamp - _stepper_config->pulse_time_stamp > STEP_PULSE_LENGTH || currnet_time_stamp < _stepper_config->pulse_time_stamp)
  {
    digitalWrite(_stepper_config->step_pin[X_AXIS], LOW);
    digitalWrite(_stepper_config->step_pin[Y_AXIS], LOW);
    digitalWrite(_stepper_config->step_pin[Z_AXIS], LOW);
    _stepper_config->pulse_time_stamp = 0;
  }
}

void StepperController::move_(int steps_mask, int current_direction_mask)
{
  unsigned long currnet_time_stamp = micros();
  // start of movement
  if (steps_mask != 0 && _stepper_config->move_time_stamp == 0)
  {
    _stepper_config->move_time_stamp = micros();
  }
  else if (_stepper_config->move_time_stamp != 0 && currnet_time_stamp - _stepper_config->move_time_stamp > _stepper_config->steps_rate)
  {
    //          || currnet_time_stamp < _stepper_config -> move_time_stamp
    this->setDirection(current_direction_mask);
    this->moveStep(steps_mask, current_direction_mask);
    _stepper_config->move_time_stamp = 0;

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

void StepperController::moveToPosition(const int *next_position)
{
  /**
  Calculation explained:
  - for each axis, we will calculate the Delta value - i.e. the amount of steps it should execute
  - The Dominant axis will be the one which will hold the largest Delta

  Each step of The dominant axis will be excuted in a constant time interval.
  for each of these steps (the dominant axis steps), we will try to determine
  rather a given axis should preform a concurrent step.

  for each axis:
  x_steps_interval = (dominant_axis / Dx)
  y_steps_interval  = (dominant_axis / Dy)
  z_steps_interval  = (dominant_axis / Dz)

  where steps interval is the amount
  of steps (of the dominant axis) that should pass until
  we excute the next cuncurrent step of that axis.

  **/
  const int *current_position = getStepsCount();
  const int dx = abs(current_position[X_AXIS] - next_position[X_AXIS]);
  const int dy = abs(current_position[Y_AXIS] - next_position[Y_AXIS]);
  const int dz = abs(current_position[Z_AXIS] - next_position[Z_AXIS]);
  const int dominant_axis = max(max(dx, dy), dz);
  int x_step_value = 0;
  int y_step_value = 0;
  int z_step_value = 0;
  int current_step_mask = 0;
  int current_direction_mask = 0;
  current_direction_mask = getLineDirectionMask(current_position, next_position);
  this->setEnable(true);
  this->setDirection(current_direction_mask);

  for (int i = 0; i <= dominant_axis; i++)
  {
    current_step_mask = 0;
    if (dx && (x_step_value >= dominant_axis))
    {
      current_step_mask = current_step_mask | (1 << X_AXIS);
      x_step_value -= dominant_axis;
    }
    if (dy && (y_step_value >= dominant_axis))
    {
      current_step_mask = current_step_mask | (1 << Y_AXIS);
      y_step_value -= dominant_axis;
    }
    if (dz && (z_step_value >= dominant_axis))
    {
      current_step_mask = current_step_mask | (1 << Z_AXIS);
      z_step_value -= dominant_axis;
    }

    x_step_value += dx;
    y_step_value += dy;
    z_step_value += dz;

    this->moveStep(current_step_mask, current_direction_mask);
    delayMicroseconds(_stepper_config->steps_rate);
  }
  this->setEnable(false);
}

void StepperController::initSegmentPlan(struct segment_plan *seg_p, const int *target_pos)
{
  seg_p->current_position = getStepsCount();
  seg_p->target_position = target_pos;
  seg_p->dx = abs(seg_p->current_position[X_AXIS] - target_pos[X_AXIS]);
  seg_p->dy = abs(seg_p->current_position[Y_AXIS] - target_pos[Y_AXIS]);
  seg_p->dz = abs(seg_p->current_position[Z_AXIS] - target_pos[Z_AXIS]);
  seg_p->dominant_axis = max(max(seg_p->dx, seg_p->dy), seg_p->dz);
  seg_p->x_step_value = 0;
  seg_p->y_step_value = 0;
  seg_p->z_step_value = 0;
  // Set steps directions
  seg_p->current_direction_mask = getLineDirectionMask(seg_p->current_position, seg_p->target_position);
  seg_p->current_step_mask = 0;
  seg_p->segment_is_enabled = false;
}

void StepperController::moveToPosition(struct segment_plan *seg_p)
{
  if (seg_p->current_position[X_AXIS] != seg_p->target_position[X_AXIS] || seg_p->current_position[Y_AXIS] != seg_p->target_position[Y_AXIS] || seg_p->current_position[Z_AXIS] != seg_p->target_position[Z_AXIS])
  {
    if (!seg_p->segment_is_enabled)
    {
      this->setEnable(true);
      this->setDirection(seg_p->current_direction_mask);
      seg_p->segment_is_enabled = true;
    }
    seg_p->current_step_mask = 0;
    if (seg_p->dx && (seg_p->x_step_value >= seg_p->dominant_axis))
    {
      seg_p->current_step_mask = seg_p->current_step_mask | (1 << X_AXIS);
      seg_p->x_step_value -= seg_p->dominant_axis;
    }
    if (seg_p->dy && (seg_p->y_step_value >= seg_p->dominant_axis))
    {
      seg_p->current_step_mask = seg_p->current_step_mask | (1 << Y_AXIS);
      seg_p->y_step_value -= seg_p->dominant_axis;
    }
    if (seg_p->dz && (seg_p->z_step_value >= seg_p->dominant_axis))
    {
      seg_p->current_step_mask = seg_p->current_step_mask | (1 << Z_AXIS);
      seg_p->z_step_value -= seg_p->dominant_axis;
    }

    seg_p->x_step_value += seg_p->dx;
    seg_p->y_step_value += seg_p->dy;
    seg_p->z_step_value += seg_p->dz;

    this->move_(seg_p->current_step_mask, seg_p->current_direction_mask);
  }
  else
  {
    this->setEnable(false);
    seg_p->segment_is_enabled = true;
  }
}
