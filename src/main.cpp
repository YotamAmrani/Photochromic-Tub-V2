#include <Arduino.h>
#include "StepperController.h"
#include "Planner.h"
#include "JoystickInterface.h"
#include "Drawings.h"

// DEFINITIONS:
void printCurrentPosition();

sys_state state = {IDLE, 0};
StepperController stepperC = StepperController();
int target[N_AXIS] = {2500, 2500, 0};
const int *current_position = stepperC.getStepsCount();
segment_plan seg_p = {0};
Planner pl = Planner(&stepperC, &seg_p);

int current_steps_mask = 0;
int current_direction_mask = 0;

void stateHandler(int current_steps_mask, StepperController *stepperC)
{
    // if movement was deteced
    if (current_steps_mask)
    {
        stepperC->setEnable(true);
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
            stepperC->setEnable(false);
        }
    }
}

void toggleLed(sys_state *state)
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

void autoHoming(StepperController *stepperC)
{
    Serial.println("Auto homing! ");
    stepperC->setStepsRate(AUTO_HOME_STEPS_RATE);
    stepperC->setEnable(true);
    while (digitalRead(X_LIMIT_SW_PIN))
    {
        stepperC->moveStep(1, 1);
    }
    while (digitalRead(Y_LIMIT_SW_PIN))
    {
        stepperC->moveStep(2, 2);
    }
    stepperC->setStepsCount(0, 0, 0);
    stepperC->setEnable(false);
    stepperC->setStepsRate(STEPS_RATE);
    printCurrentPosition();
}

void printCurrentPosition()
{
    Serial.println("Position: ");
    Serial.print(stepperC.getStepsCount()[X_AXIS]);
    Serial.print(",");
    Serial.print(stepperC.getStepsCount()[Y_AXIS]);
    Serial.print(",");
    Serial.println(stepperC.getStepsCount()[Z_AXIS]);
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
    autoHoming(&stepperC);

    pl.initSegmentPlan(target);
    pl.printStepper();
    temp = micros();
    stepperC.setStepsRate(500);
    stepperC.setEnable(true);
    state.sys_mode = PRINT;

    Serial.println(micros() - temp);
    temp = micros();
    pl.loadDrawing(squareDrawing);
}

void loop()
{
    /** GET INPUT MASK **/
    current_steps_mask = 0;
    current_direction_mask = 0;
    getMovementMask(&current_steps_mask, &current_direction_mask);
    stateHandler(current_steps_mask, &stepperC);
    toggleLed(&state);

    if (state.sys_mode == MOVE)
    {
        stepperC.moveStep(current_steps_mask, current_direction_mask);
    }
    else if (state.sys_mode == PRINT)
    {
        // pl.moveToPosition();
        pl.plotDrawing(squareDrawing, 10);
    }
}
