
#ifndef STEPPER_H
#include <Arduino.h>
#include "Settings.h"
#define STEPPER_H

struct step_plan
{
    unsigned long steps_rate;
    int steps_mask;
    int direction_mask;
    bool led_state;
};

class Stepper
{
private:
    const int step_pin_;
    const int dir_pin_;
    const int en_pin_;
    const bool invert_direction_; // case flip mototr de=irection is needed - turn on
    unsigned long move_time_stamp_;
    unsigned long steps_rate_;
    int steps_counter_;

    void step(int step);

public:
    Stepper(int step_pin, int dir_pin, int en_pin, bool invert_direction);

    void set_direction(int step_mask);

    int get_direction();

    void set_steps_rate(unsigned long steps_rate);

    void move_step(int steps_mask);

    int get_steps_count();

    void set_steps_count(int steps);

    //   void set_enable(bool isEnabled);
};

#endif
