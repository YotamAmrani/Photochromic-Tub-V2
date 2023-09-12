#ifndef DRAWINGS_H
#define DRAWINGS_H
#include "Settings.h"
#include <Arduino.h>
// #include <String.h>

class Drawing
{
private:
public:
    // String drawing_name_;
    const uint16_t (*segments_)[N_AXIS];
    const int drawing_size_;
    const unsigned long drawing_speed_;
    Drawing(const uint16_t segments[][N_AXIS], int drawing_size, const unsigned long drawing_speed);
    // void print_name();
};

#endif
