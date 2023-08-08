#ifndef SETTINGS_H
#define SETTINGS_H

// Macros
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define N_AXIS 3
#define bit_istrue(x, mask) ((x & mask) != 0)
#define bit_to_sign(x, mask) (((x & mask) != 0) ? -1 : 1)
#define DIRECTION_INVERT_MASK 2

// STEPERS CONFIGURATIONS
#define X_STEP_PIN 5
#define Y_STEP_PIN 6
#define Z_STEP_PIN 7
#define X_DIR_PIN 2
#define Y_DIR_PIN 3
#define Z_DIR_PIN 4
#define EN_PIN 8

// LIMIT SWITCHES
#define X_LIMIT_SW_PIN 9
#define Y_LIMIT_SW_PIN 10

// JOYSTICK PINS
#define X_INPUT_PIN A2
#define Y_INPUT_PIN A3
#define Z_INPUT_PIN A4
#define X_IDLE_VALUE 445
#define Y_IDLE_VALUE 155
#define LEFT_VALUE 835
#define RIGHT_VALUE 0
#define FORWARD_VALUE 595
#define BACK_VALUE 0
#define DOWN_VALUE 835
#define UP_VALUE 0
#define X_NOISE 250
#define Y_NOISE 100

// #define LED_INPUT_PIN A4

// LED
#define LED_PIN 11
#define LED_TURN_ON_VALUE 255

// SYSTEM CONFIGURATIONS
#define STEP_PULSE_LENGTH 5
#define STEPS_RATE 500
#define X_STEPS_PER_MM 40
#define Y_STEPS_PER_MM 40
#define Z_STEPS_PER_MM 10
#define steps_to_mm(steps, ratio) (steps / ratio)
#define mm_to_steps(mm, ratio) (mm * ratio)

template <typename T>
int sgn(T val)
{
  return (T(0) < val) - (val < T(0));
}

enum State
{
  IDLE,
  MOVE,
  PRINT
};
struct sys_state
{
  State sys_mode;
  long unsigned last_move_time_stamp;
};

#endif
