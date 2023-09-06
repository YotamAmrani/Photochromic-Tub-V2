#include "Drawings.h"

Drawing::Drawing(double segments[][N_AXIS], int drawing_size)
    : segments_(segments), drawing_size_(drawing_size)
{
    // drawing_name_ = String(drawing_name);
    // Serial.println("name");
    // Serial.println(drawing_name_.length());
}

// void Drawing::print_name()
// {
//     Serial.println(drawing_name_.length());
//     for (unsigned int i = 0; i < drawing_name_.length(); i++)
//     {
//         Serial.print("y");
//         Serial.print(drawing_name_.charAt(i));
//     }
// }