#include <Arduino.h>
#include "StepperController.h"
#include "Planner.h"
#include "JoystickInterface.h"
#include "DrawingObjects.h"
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

void printDrawing(Drawing test)
{

    for (int i = 0; i < test.drawing_size_; i++)
    {
        const double *temp = test.segments_[i];
        Serial.print(temp[X_AXIS]);
        Serial.print(",");
        Serial.print(temp[Y_AXIS]);
        Serial.print(",");
        Serial.println(temp[Z_AXIS]);
    }
}

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
        pl.load_drawing(&drawings[1]);
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
    // auto_homing(&stepper_c);
    // Serial.println("Print drawing: ");
    // printDrawing(drawings[0]);

    pl.load_drawing(&drawings[1]);
    // stepper_c.set_enable(true);
    // Serial.print("testing: ");
    // Serial.println(pl.current_drawing_->drawing_size_);
    // for (int i = 0; i < pl.current_drawing_->drawing_size_; i++)
    // {
    //     Serial.print(pl.current_drawing_->segments_[i][X_AXIS]);
    //     Serial.print(",");
    //     Serial.print(pl.current_drawing_->segments_[i][Y_AXIS]);
    //     Serial.print(",");
    //     Serial.println(pl.current_drawing_->segments_[i][Z_AXIS]);
    // }

    state.sys_mode = IDLE;
}

void loop()
{
    // long unsigned int t = micros();
    /** GET INPUT MASK **/
    current_steps_mask = 0;
    current_direction_mask = 0;
    // getMovementMask(&current_steps_mask, &current_direction_mask);
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
