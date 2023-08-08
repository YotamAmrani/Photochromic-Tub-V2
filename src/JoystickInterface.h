#ifndef JOYSTICK_INTERFACE_H
#define JOYSTICK_INTERFACE_H

#include "Settings.h"
#include <Arduino.h>
// JoyStick interface

void editADCPrescaler();

void printJoystickInput();

void getMovementMask(int *current_steps_mask, int *current_direction_mask);

void getMovementMaskD(int *current_steps_mask, int *current_direction_mask);

#endif
