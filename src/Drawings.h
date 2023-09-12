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
    const unsigned int (*segments_)[N_AXIS];
    const int drawing_size_;
    Drawing(unsigned int segments[][N_AXIS], int drawing_size);
    // void print_name();
};

#endif
