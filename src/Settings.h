#ifndef SETTINGS_H
#define SETTINGS_H

// Instructions indices
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define LED_VALUE 3

#define N_AXIS 3
#define N_INSTRUCTIONS 4
#define bit_istrue(x, mask) ((x & mask) != 0)
#define bit_to_sign(x, mask) (((x & mask) != 0) ? -1 : 1)
#define DIRECTION_INVERT_MASK 2

// LED
#define LED_PIN 11
#define LED_TURN_ON_VALUE 255
#define LED_DEBOUNCE_TIME 300

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
#define X_INPUT_PIN A1
#define Y_INPUT_PIN A2
#define Z_INPUT_PIN A3
#define IDLE_VALUE 445
#define LEFT_VALUE 835
#define RIGHT_VALUE 0
#define FORWARD_VALUE 835
#define BACK_VALUE 0
#define DOWN_VALUE 835
#define UP_VALUE 0
#define NOISE_VALUE 100

// #define LED_INPUT_PIN A4

// SYSTEM CONFIGURATIONS
#define STEP_PULSE_LENGTH 20
#define STEPS_RATE 500
#define X_STEPS_PER_MM 40
#define Y_STEPS_PER_MM 40
#define Z_STEPS_PER_MM 100

// SOFT LIMITS SETTINGS
#define ENABLE_SOFT_LIMIT 1 // uncomment to disable soft limits
#define AUTO_HOME_STEPS_RATE 1500
#define X_MM_LIMIT 150
#define Y_MM_LIMIT 150
#define Z_MM_LIMIT 200

// AUTO HOME OFFSET
#define MM_OFFSET 5

// AUTO PRINTING8
#define PENDING_TIME (1000000 * 180)

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
