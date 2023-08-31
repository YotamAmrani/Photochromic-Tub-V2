#ifndef DRAWINGS_H
#define DRAWINGS_H
#include "Settings.h"
#include <Arduino.h>

class Drawing
{
private:
public:
    const String drawing_name_;
    const double (*segments_)[N_AXIS];
    const int drawing_size_;
    Drawing(String drawing_name, double segments[][N_AXIS], int drawing_size);
};

#endif
