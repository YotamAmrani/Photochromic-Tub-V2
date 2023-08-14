#include <Arduino.h>
#include "StepperController.h"
#include "Planner.h"
#include "JoystickInterface.h"
#include "Drawings.h"

// DEFINITIONS:
void print_current_position();

sys_state state = {IDLE, 0};
StepperController stepper_c = StepperController();
int target[N_AXIS] = {2500, 2500, 0};
const int *current_position = stepper_c.get_steps_count();
segment_plan seg_p = {0};
Planner pl = Planner(&stepper_c, &seg_p);

int current_steps_mask = 0;
int current_direction_mask = 0;

void state_handler(int current_steps_mask, StepperController *stepper_c)
{
    // if movement was deteced
    if (current_steps_mask)
    {
        stepper_c->set_enable(true);
        if (state.sys_mode == IDLE)
        {
            state.sys_mode = MOVE;
        }
        else if (state.sys_mode == PRINT)
        {
            state.sys_mode = MOVE;
            // reset the current state
            // change to move state
        }
        state.last_move_time_stamp = millis();
    }
    else
    {
        if (state.sys_mode == MOVE && (millis() - state.last_move_time_stamp) > LED_DEBOUNCE_TIME)
        {

            state.sys_mode = IDLE;
            stepper_c->set_enable(false);
        }
    }
}

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

void auto_homing(StepperController *stepper_c)
{
    Serial.println("Auto homing! ");
    stepper_c->set_steps_rate(AUTO_HOME_STEPS_RATE);
    stepper_c->set_enable(true);
    while (digitalRead(X_LIMIT_SW_PIN))
    {
        stepper_c->move_step(1, 1);
    }
    while (digitalRead(Y_LIMIT_SW_PIN))
    {
        stepper_c->move_step(2, 2);
    }
    stepper_c->set_steps_count(0, 0, 0);
    stepper_c->set_enable(false);
    stepper_c->set_steps_rate(STEPS_RATE);
    print_current_position();
}

void print_current_position()
{
    Serial.println("Position: ");
    Serial.print(stepper_c.get_steps_count()[X_AXIS]);
    Serial.print(",");
    Serial.print(stepper_c.get_steps_count()[Y_AXIS]);
    Serial.print(",");
    Serial.println(stepper_c.get_steps_count()[Z_AXIS]);
}

void setup()
{

    Serial.begin(115200);
    /** Init Joystick input pins **/
    editADCPrescaler();
    initJoystickPins();

    // int mm_to_move = 100;
    // int steps_to_move = mm_to_steps(mm_to_move, X_STEPS_PER_MM);
    unsigned long temp = 0;
    auto_homing(&stepper_c);

    pl.init_segment_plan(target);
    pl.print_stepper();
    temp = micros();
    stepper_c.set_enable(true);
    state.sys_mode = PRINT;

    Serial.println(micros() - temp);
    temp = micros();
    pl.load_drawing(squareDrawing);
}

void loop()
{
    /** GET INPUT MASK **/
    current_steps_mask = 0;
    current_direction_mask = 0;
    getMovementMask(&current_steps_mask, &current_direction_mask);
    state_handler(current_steps_mask, &stepper_c);
    toggle_led(&state);

    if (state.sys_mode == MOVE)
    {
        stepper_c.move_step(current_steps_mask, current_direction_mask);
    }
    else if (state.sys_mode == PRINT)
    {
        // pl.moveToPosition();
        pl.plot_drawing(squareDrawing, 10);
    }
}
