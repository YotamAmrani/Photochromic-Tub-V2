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

// double only_z[4][N_AXIS] = {
//     {37.49, 45.24, 16.36},
//     {33.61, 44.41, 16.86},
//     {29.73, 43.59, 17.37},
//     {25.85, 42.76, 17.88}};

#endif
