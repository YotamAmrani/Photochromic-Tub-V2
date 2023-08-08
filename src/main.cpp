#include <Arduino.h>
#include "StepperController.h"
#include "Planner.h"
#include "JoystickInterface.h"
#include "Drawings.h"

// DEFINITIONS:
void printCurrentPosition();

// Coordinates system
stepper_config stepper_c = {{X_AXIS, Y_AXIS, Z_AXIS},
                            {X_STEP_PIN, Y_STEP_PIN, Z_STEP_PIN},
                            {X_DIR_PIN, Y_DIR_PIN, Z_DIR_PIN},
                            EN_PIN,
                            micros(),
                            micros(),
                            STEPS_RATE,
                            0};

StepperController stepperC = StepperController(&stepper_c);
int target[N_AXIS] = {1000, 1000, 0};
const int *current_position = stepperC.getStepsCount();
segment_plan seg_p = {0};
Planner pl = Planner(&stepperC, &seg_p);

int current_steps_mask = 0;
int current_direction_mask = 0;

sys_state state = {IDLE, 0};

void stateHandler(int current_steps_mask, StepperController *StepperC)
{
    // Turn on - not idle
    if (state.sys_mode == IDLE && current_steps_mask)
    {
        state.sys_mode = MOVE;
        state.last_move_time_stamp = 0;
        StepperC->setEnable(true);
    }
    // Turn off - moving
    if (state.sys_mode == MOVE && !current_steps_mask)
    {
        state.sys_mode = IDLE;
        state.last_move_time_stamp = micros();
        StepperC->setEnable(false);
    }
}

void toggleLed(sys_state *state)
{
    if (state->sys_mode == MOVE)
    {
        analogWrite(LED_PIN, LED_TURN_ON_VALUE);
    }
    else
    {
        analogWrite(LED_PIN, LOW);
    }
}

void autoHoming(StepperController *StepperC)
{
    Serial.println("Auto homing! ");
    StepperC->setEnable(true);
    while (digitalRead(X_LIMIT_SW_PIN))
    {
        StepperC->move_(1, 1);
    }
    while (digitalRead(Y_LIMIT_SW_PIN))
    {
        StepperC->move_(2, 2);
    }
    StepperC->setStepsCount(0, 0, 0);
    StepperC->setEnable(false);
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
    pinMode(X_INPUT_PIN, INPUT);
    pinMode(Y_INPUT_PIN, INPUT);
    pinMode(Z_INPUT_PIN, INPUT);
    pinMode(X_LIMIT_SW_PIN, INPUT_PULLUP);
    pinMode(Y_LIMIT_SW_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // int mm_to_move = 100;
    // int steps_to_move = mm_to_steps(mm_to_move, X_STEPS_PER_MM);
    unsigned long temp = 0;
    autoHoming(&stepperC);

    // stepperC.initSegmentPlan(&seg_p, target);
    pl.initSegmentPlan(target);
    pl.printStepper();
    temp = micros();
    stepperC.setStepsRate(1000);
    stepperC.setEnable(true);
    //  while(current_position[X_AXIS] <= target[X_AXIS]){
    //    Serial.println(current_position[X_AXIS]);
    //    stepperC.move_(3,0);
    //    }
    //  stepperC.setEnable(false);

    Serial.println(micros() - temp);
    temp = micros();
}

void loop()
{
    /** GET INPUT MASK **/
    current_steps_mask = 0;
    current_direction_mask = 0;
    getMovementMask(&current_steps_mask, &current_direction_mask);
    stateHandler(current_steps_mask, &stepperC);
    toggleLed(&state);
    // stepperC.move_(current_steps_mask, current_direction_mask);

    // stepperC.moveToPosition(&seg_p);
    pl.moveToPosition(&seg_p);
    if (state.sys_mode == IDLE)
    {
    }

    // move_ version is non blocking currently - may be called whenever we want
    //  StepperC.setEnable(true);
    //  if(current_position[X_AXIS] <= target[X_AXIS]){
    //    Serial.println(current_position[X_AXIS]);
    //    StepperC.move_(3,0);
    //    }
    //  StepperC.setEnable(false);
}
