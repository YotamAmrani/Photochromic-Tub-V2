#include "JoystickInterface.h"

void editADCPrescaler()
{
  /** ADC Settings **/
  //  https://forum.arduino.cc/t/faster-analog-read/6604/3
  // http://gammon.com.au/adc
  ADCSRA &= ~(bit(ADPS0) | bit(ADPS1) | bit(ADPS2)); // clear prescaler bits
  // uncomment as required
  //  ADCSRA |= bit (ADPS0);                               //   2
  //  ADCSRA |= bit (ADPS1);                               //   4
  //  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8
  ADCSRA |= bit(ADPS2); //  16
                        //  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32
                        //  ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64
                        //  ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128
}

void printJoystickInput()
{
  // put your main code here, to run repeatedly:
  Serial.print("X axis:");
  Serial.print(analogRead(X_INPUT_PIN));
  Serial.print(",");
  Serial.print("Y axis:");
  Serial.print(analogRead(Y_INPUT_PIN));
  Serial.print(",");
  Serial.print("Z axis:");
  Serial.println(analogRead(Z_INPUT_PIN));
  delay(5);
}

void getMovementMask(int *current_steps_mask, int *current_direction_mask)
{
  *current_steps_mask = 0;
  *current_direction_mask = 0;
  int x_input = analogRead(X_INPUT_PIN);
  int y_input = analogRead(Y_INPUT_PIN);
  int z_input = analogRead(Z_INPUT_PIN);

  /* Move X AXIS */
  if (x_input > (IDLE_VALUE + 100))
  {
    *current_steps_mask = *current_steps_mask | (1 << X_AXIS);
    *current_direction_mask = *current_direction_mask | (1 << X_AXIS);
  }
  else if (x_input < (IDLE_VALUE - NOISE_VALUE))
  {
    *current_steps_mask = *current_steps_mask | (1 << X_AXIS);
  }

  /* Move Y AXIS */
  if (y_input > (IDLE_VALUE + NOISE_VALUE))
  {
    *current_steps_mask = *current_steps_mask | (1 << Y_AXIS);
  }
  else if (y_input < (IDLE_VALUE - NOISE_VALUE))
  {
    *current_steps_mask = *current_steps_mask | (1 << Y_AXIS);
    *current_direction_mask = *current_direction_mask | (1 << Y_AXIS);
  }

  /* Move Z AXIS */
  if (z_input > (IDLE_VALUE + 100))
  {
    *current_steps_mask = *current_steps_mask | (1 << Z_AXIS);
    *current_direction_mask = *current_direction_mask | (1 << Z_AXIS);
  }
  else if (z_input < (IDLE_VALUE - NOISE_VALUE))
  {
    *current_steps_mask = *current_steps_mask | (1 << Z_AXIS);
  }
}

void getMovementMaskD(int *current_steps_mask, int *current_direction_mask)
{
  *current_steps_mask = 0;
  *current_direction_mask = 0;

  /* Move X AXIS */
  if (digitalRead(X_INPUT_PIN) > (IDLE_VALUE + 100))
  {
    *current_steps_mask = *current_steps_mask | (1 << X_AXIS);
    *current_direction_mask = *current_direction_mask | (1 << X_AXIS);
  }
  else if (digitalRead(X_INPUT_PIN) < (IDLE_VALUE - NOISE_VALUE))
  {
    *current_steps_mask = *current_steps_mask | (1 << X_AXIS);
  }

  /* Move Y AXIS */
  if (digitalRead(Y_INPUT_PIN) > (IDLE_VALUE + NOISE_VALUE))
  {
    *current_steps_mask = *current_steps_mask | (1 << Y_AXIS);
  }
  else if (digitalRead(Y_INPUT_PIN) < (IDLE_VALUE - NOISE_VALUE))
  {
    *current_steps_mask = *current_steps_mask | (1 << Y_AXIS);
    *current_direction_mask = *current_direction_mask | (1 << Y_AXIS);
  }
}

void initJoystickPins()
{
  pinMode(X_INPUT_PIN, INPUT);
  pinMode(Y_INPUT_PIN, INPUT);
  pinMode(Z_INPUT_PIN, INPUT);
  pinMode(X_LIMIT_SW_PIN, INPUT_PULLUP);
  pinMode(Y_LIMIT_SW_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

//    /* Move X AXIS */
//     if(analogRead(X_INPUT_PIN) > (RIGHT_VALUE - NOISE) and analogRead(X_INPUT_PIN) < (RIGHT_VALUE + NOISE)){
//        current_steps_mask = current_steps_mask | (1<<X_AXIS);
//      }
//     else if(analogRead(X_INPUT_PIN) > (LEFT_VALUE - NOISE) and analogRead(X_INPUT_PIN) < (LEFT_VALUE + NOISE)){
//        current_steps_mask = current_steps_mask | (1<<X_AXIS);
//        current_direction_mask = current_direction_mask | (1<<X_AXIS);
//      }
//
//     /* Move Y AXIS */
//     if(analogRead(Y_INPUT_PIN) > (FORWARD_VALUE - NOISE) and analogRead(Y_INPUT_PIN) < (FORWARD_VALUE + NOISE)){
//        current_steps_mask = current_steps_mask | (1<<Y_AXIS);
//
//      }
//     else if(analogRead(Y_INPUT_PIN) > (BACK_VALUE - NOISE) and analogRead(Y_INPUT_PIN) < (BACK_VALUE + NOISE)){
//        current_direction_mask = current_direction_mask | (1<<Y_AXIS);
//        current_steps_mask = current_steps_mask | (1<<Y_AXIS);
//      }
