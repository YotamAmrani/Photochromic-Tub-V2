#include "Drawings.h"

Drawing::Drawing(String drawing_name, double segments[][N_AXIS], int drawing_size)
    : drawing_name_(drawing_name), segments_(segments), drawing_size_(drawing_size)
{
}