#include <Arduino.h>
#include "StepperController.h"
#include "Planner.h"
#include "JoystickInterface.h"
#include "Drawings.h"
#include "Settings.h"

// #include "avr8-stub.h"
// #include "app_api.h" // only needed with flash breakpoints

// DEFINITIONS:
void print_current_position();
void toggle_led(bool turn_on);

sys_state state = {IDLE, micros()};
StepperController stepper_c = StepperController();
int current_steps_mask = 0;
int current_direction_mask = 0;
int target[N_AXIS] = {0, 0, 0};
const int *current_position = stepper_c.get_steps_count();
segment_plan seg_p = {0};
Planner pl = Planner(&stepper_c, &seg_p);
double testing[25][N_AXIS] = {{35.17, 38.75, 0},
                              {31.58, 39.78, 1.44},
                              {28.64, 40.14, 2.87},
                              {29.54, 36.52, 4.31},
                              {31, 34.7, 5.6},
                              {33.85, 37.35, 6.53},
                              {36.7, 40.01, 7.46},
                              {36.7, 41.6, 8.32},
                              {32.77, 41.74, 9.07},
                              {28.85, 41.87, 9.83},
                              {24.92, 42.01, 10.59},
                              {26.15, 38.93, 11.34},
                              {27.99, 35.46, 12.1},
                              {29.84, 31.99, 12.85},
                              {31.73, 31.04, 13.54},
                              {33.7, 34.48, 14.11},
                              {35.67, 37.91, 14.68},
                              {37.64, 41.35, 15.26},
                              {39.61, 44.78, 15.83},
                              {37.49, 45.24, 16.36},
                              {33.61, 44.41, 16.86},
                              {29.73, 43.59, 17.37},
                              {25.85, 42.76, 17.88},
                              {21.97, 41.94, 18.39},
                              {21.09, 40.14, 18.9}};
Drawing drawings[1] = {Drawing("testing", testing, 25)};

void state_handler(int current_steps_mask, StepperController *stepper_c)
{
    // if movement was deteced
    if (current_steps_mask)
    {

        stepper_c->set_enable(true);
        if (state.sys_mode == IDLE)
        {
            state.sys_mode = MOVE;
            toggle_led(true); // turn led on
        }
        else if (state.sys_mode == PRINT)
        {
            state.sys_mode = MOVE;
            toggle_led(true); // turn led on
            // reset the current state
            // change to move state
        }
        state.last_move_time_stamp = micros();
    }
    else
    {
        if (state.sys_mode == MOVE && (micros() - state.last_move_time_stamp) > LED_DEBOUNCE_TIME)
        {
            state.sys_mode = IDLE;
            stepper_c->set_enable(false);
            toggle_led(false); // turn led off
        }
        else if (state.sys_mode == PRINT && pl.is_drawing_finished())
        {
            state.sys_mode = IDLE;
            toggle_led(false);
            state.last_move_time_stamp = micros();
        }
    }
}

void toggle_led(bool turn_on)
{
    if (!digitalRead(LED_PIN) && turn_on)
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
    while (stepper_c->get_steps_count()[X_AXIS] < mm_to_steps(MM_OFFSET, X_STEPS_PER_MM))
    {
        stepper_c->move_step(1, 0);
    }

    while (stepper_c->get_steps_count()[Y_AXIS] < mm_to_steps(MM_OFFSET, Y_STEPS_PER_MM))
    {
        stepper_c->move_step(2, 0);
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

void initialize_auto_print()
{
    if (micros() - state.last_move_time_stamp > PENDING_TIME)
    {
        // running_time = micros();
        pl.reset_drawing();
        pl.load_drawing(&drawings[0]);
        // toggle_led(true);
        stepper_c.set_enable(true);
        state.sys_mode = PRINT;
    }
}

void setup()
{

    Serial.begin(115200);
    /** Init Joystick input pins **/
    editADCPrescaler();
    initJoystickPins();
    /** AUTO HOME**/
    auto_homing(&stepper_c);

    // pl.load_drawing(testing, 25);
    state.sys_mode = IDLE;
}

void loop()
{
    // long unsigned int t = micros();
    /** GET INPUT MASK **/
    current_steps_mask = 0;
    current_direction_mask = 0;
    getMovementMask(&current_steps_mask, &current_direction_mask);
    state_handler(current_steps_mask, &stepper_c);

    switch (state.sys_mode)
    {
    case MOVE:
        stepper_c.move_step(current_steps_mask, current_direction_mask);
        break;
    case PRINT:
        pl.plot_drawing();
        break;
    case IDLE:
        initialize_auto_print();
        break;
    default:
        // code block
        break;
    }
    // Serial.println(micros() - t);
}
