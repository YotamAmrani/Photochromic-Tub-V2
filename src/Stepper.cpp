#include "Stepper.h"

Stepper::Stepper(int step_pin, int dir_pin, int en_pin, bool invert_direction) : step_pin_(step_pin), dir_pin_(dir_pin), en_pin_(EN_PIN),
                                                                                 invert_direction_(invert_direction), steps_counter_(0)
{
    // Initializing values
    move_time_stamp_ = micros();
    steps_rate_ = STEPS_RATE;
    // Declare pins as Outputs
    pinMode(step_pin_, OUTPUT);
    pinMode(dir_pin_, OUTPUT);
    pinMode(en_pin_, OUTPUT);
    // this->set_enable(false);
}

/*    SETTERS    **/
void Stepper::set_steps_rate(unsigned long steps_rate)
{
    if (steps_rate >= 0)
    {
        steps_rate_ = steps_rate;
        Serial.println(steps_rate_);
    }
}

void Stepper::set_direction(int step_mask)
{

    int direction_pin_output = LOW;
    // Case negative - turn direction pin on
    if (step_mask < 0)
    {
        direction_pin_output = HIGH;
    }
    if (invert_direction_)
    {
        direction_pin_output = !direction_pin_output;
    }
    digitalWrite(dir_pin_, direction_pin_output);
}

void Stepper::set_steps_count(int steps)
{
    steps_counter_ = steps;
}

/*    GETTERS    **/
int Stepper::get_steps_count()
{
    return steps_counter_;
}

int Stepper::get_direction()
{
    int direction = digitalRead(dir_pin_) ? -1 : 1;
    if (invert_direction_)
    {
        direction *= -1;
    }
    return direction;
}

/*    MOVEMENT METHODS    **/
void Stepper::step(int step_mask)
{
    digitalWrite(step_pin_, HIGH);
    delayMicroseconds(STEP_PULSE_LENGTH);
    digitalWrite(step_pin_, LOW);
    steps_counter_ += step_mask;
}

void Stepper::move_step(int step_mask)
{
    // turn sed pulse
    if (step_mask && (micros() - move_time_stamp_ > steps_rate_))
    {
        this->step(step_mask);       // Send step
        move_time_stamp_ = micros(); // reset timer
    }
    else
    {
        Serial.println(micros() - move_time_stamp_);
    }
}
