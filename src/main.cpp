#include <Arduino.h>
#include "Stepper.h"
#include "Planner.h"
#include "JoystickInterface.h"
#include "Drawings.h"
#include "Settings.h"

// DEFINITIONS:
void print_current_position();

sys_state state = {IDLE, 0};
int current_steps_mask[N_AXIS] = {0};
int target_position[N_AXIS] = {-125, 0, 0};
int current_position[N_AXIS] = {0};
Stepper axis[N_AXIS] = {Stepper(X_STEP_PIN, X_DIR_PIN, EN_PIN, false),
                        Stepper(Y_STEP_PIN, Y_DIR_PIN, EN_PIN, true),
                        Stepper(Z_STEP_PIN, Z_DIR_PIN, EN_PIN, false)};

Planner pl = Planner(axis);

// void state_handler(int current_steps_mask, StepperController *stepper_c)
// {
//     // if movement was deteced
//     if (current_steps_mask)
//     {
//         stepper_c->set_enable(true);
//         // print_current_position();
//         stepper_c->set_enable(true);
//         if (state.sys_mode == IDLE)
//         {
//             state.sys_mode = MOVE;
//         }
//         else if (state.sys_mode == PRINT)
//         {
//             state.sys_mode = MOVE;
//             // reset the current state
//             // change to move state
//         }
//         state.last_move_time_stamp = millis();
//     }
//     else
//     {
//         if (state.sys_mode == MOVE && (millis() - state.last_move_time_stamp) > LED_DEBOUNCE_TIME)
//         {

//             state.sys_mode = IDLE;
//             stepper_c->set_enable(false);
//         }
//     }
// }

void toggle_led(sys_state *state)
{
    if (!digitalRead(LED_PIN) && state->sys_mode == MOVE)
    {
        analogWrite(LED_PIN, LED_TURN_ON_VALUE);
    }
    else
    {
        analogWrite(LED_PIN, LOW);
    }
}

// void auto_homing(StepperController *stepper_c)
// {
//     Serial.println("Auto homing! ");
//     stepper_c->set_steps_rate(AUTO_HOME_STEPS_RATE);
//     stepper_c->set_enable(true);
//     while (digitalRead(X_LIMIT_SW_PIN))
//     {
//         stepper_c->move_step(1, 1);
//     }
//     while (digitalRead(Y_LIMIT_SW_PIN))
//     {
//         stepper_c->move_step(2, 2);
//     }
//     stepper_c->set_steps_count(0, 0, 0);
//     stepper_c->set_enable(false);
//     stepper_c->set_steps_rate(STEPS_RATE);
//     print_current_position();
// }

void print_current_position()
{
    Serial.println("Position: ");
    Serial.print(axis[X_AXIS].get_steps_count());
    Serial.print(",");
    Serial.print(axis[Y_AXIS].get_steps_count());
    Serial.print(",");
    Serial.println(axis[Z_AXIS].get_steps_count());
}

void setup()
{

    Serial.begin(115200);
    /** Init Joystick input pins **/
    editADCPrescaler();
    initJoystickPins();

    // auto_homing(&stepper_c);

    pl.init_segment_plan(target_position);
    // pl.is_segment_printing_ = true;
    // pl.load_drawing(testing, 25);
    // stepper_c.set_enable(true);
    state.sys_mode = PRINT;
}

void loop()
{
    /** GET INPUT MASK **/
    current_steps_mask[X_AXIS] = 0;
    current_steps_mask[Y_AXIS] = 0;
    current_steps_mask[Z_AXIS] = 0;
    // getMovementMask(&current_steps_mask, &current_direction_mask);
    // state_handler(current_steps_mask, &stepper_c);
    // toggle_led(&state);

    if (state.sys_mode == MOVE)
    {
        // stepper_c.move_step(current_steps_mask, current_direction_mask);
    }
    else if (state.sys_mode == PRINT)
    {
        // pl.plot_drawing();
        long unsigned int b = micros();
        pl.move_to_position(target_position);
        Serial.println(micros() - b);
    }
}
