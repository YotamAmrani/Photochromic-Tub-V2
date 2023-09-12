#include "Drawings.h"

Drawing::Drawing(const uint16_t segments[][N_AXIS], int drawing_size, const unsigned long drawing_speed)
    : segments_(segments), drawing_size_(drawing_size), drawing_speed_(drawing_speed)
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