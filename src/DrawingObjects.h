#include "Drawings.h"

// unsigned int simple_spiral[101][N_AXIS] = {{75, 75, 0},
//                                            {89, 86, 2},
//                                            {77, 101, 5},
//                                            {57, 102, 8},
//                                            {42, 89, 10},
//                                            {36, 70, 12},
//                                            {42, 50, 14},
//                                            {56, 36, 15},
//                                            {75, 30, 17},
//                                            {95, 33, 19},
//                                            {112, 44, 20},
//                                            {123, 62, 22},
//                                            {125, 82, 23},
//                                            {120, 101, 25},
//                                            {108, 117, 26},
//                                            {90, 127, 27},
//                                            {70, 130, 29},
//                                            {50, 126, 30},
//                                            {33, 115, 31},
//                                            {21, 98, 33},
//                                            {16, 79, 34},
//                                            {17, 58, 35},
//                                            {25, 40, 36},
//                                            {39, 25, 38},
//                                            {57, 16, 39},
//                                            {78, 13, 40},
//                                            {98, 17, 41},
//                                            {115, 27, 42},
//                                            {129, 42, 44},
//                                            {137, 61, 45},
//                                            {139, 81, 46},
//                                            {134, 101, 47},
//                                            {123, 118, 48},
//                                            {108, 131, 49},
//                                            {89, 139, 50},
//                                            {69, 141, 52},
//                                            {49, 136, 53},
//                                            {31, 126, 54},
//                                            {18, 111, 55},
//                                            {10, 92, 56},
//                                            {7, 72, 57},
//                                            {11, 52, 58},
//                                            {21, 34, 59},
//                                            {35, 20, 60},
//                                            {53, 10, 61},
//                                            {73, 7, 63},
//                                            {94, 10, 64},
//                                            {112, 18, 65},
//                                            {127, 32, 66},
//                                            {138, 49, 67},
//                                            {143, 69, 68},
//                                            {141, 89, 69},
//                                            {134, 108, 70},
//                                            {121, 125, 71},
//                                            {105, 136, 72},
//                                            {85, 142, 73},
//                                            {65, 142, 75},
//                                            {45, 136, 76},
//                                            {29, 125, 77},
//                                            {16, 109, 78},
//                                            {9, 90, 79},
//                                            {7, 69, 80},
//                                            {12, 50, 81},
//                                            {23, 32, 82},
//                                            {39, 19, 83},
//                                            {57, 11, 84},
//                                            {78, 9, 86},
//                                            {97, 13, 87},
//                                            {115, 24, 88},
//                                            {129, 39, 89},
//                                            {137, 57, 90},
//                                            {139, 78, 91},
//                                            {134, 98, 92},
//                                            {124, 115, 94},
//                                            {108, 128, 95},
//                                            {89, 136, 96},
//                                            {69, 137, 97},
//                                            {49, 131, 98},
//                                            {33, 119, 100},
//                                            {21, 103, 101},
//                                            {16, 83, 102},
//                                            {17, 63, 103},
//                                            {26, 44, 104},
//                                            {40, 30, 106},
//                                            {58, 21, 107},
//                                            {79, 20, 108},
//                                            {98, 26, 110},
//                                            {114, 39, 111},
//                                            {123, 57, 113},
//                                            {125, 77, 114},
//                                            {119, 96, 115},
//                                            {106, 111, 117},
//                                            {87, 120, 119},
//                                            {67, 119, 120},
//                                            {49, 109, 122},
//                                            {38, 92, 124},
//                                            {37, 72, 126},
//                                            {48, 54, 128},
//                                            {66, 47, 130},
//                                            {84, 54, 132},
//                                            {86, 72, 136}};

// triangle_spiral - NOT GOOD - Captured
// unsigned int triangle_spiral[51][N_AXIS] = {{86, 89, 0},
//                                             {74, 95, 4},
//                                             {75, 82, 8},
//                                             {93, 91, 11},
//                                             {69, 101, 15},
//                                             {73, 75, 19},
//                                             {101, 93, 22},
//                                             {63, 105, 26},
//                                             {72, 67, 30},
//                                             {107, 97, 34},
//                                             {57, 110, 38},
//                                             {71, 60, 41},
//                                             {114, 102, 45},
//                                             {50, 113, 49},
//                                             {72, 52, 52},
//                                             {120, 107, 56},
//                                             {42, 115, 60},
//                                             {74, 44, 64},
//                                             {125, 113, 68},
//                                             {34, 117, 71},
//                                             {77, 36, 75},
//                                             {129, 121, 79},
//                                             {26, 117, 82},
//                                             {81, 29, 86},
//                                             {133, 128, 90},
//                                             {17, 116, 94},
//                                             {86, 22, 98},
//                                             {124, 127, 101},
//                                             {22, 109, 105},
//                                             {89, 30, 109},
//                                             {116, 125, 112},
//                                             {28, 103, 116},
//                                             {91, 38, 120},
//                                             {109, 122, 124},
//                                             {35, 98, 128},
//                                             {92, 46, 131},
//                                             {102, 118, 135},
//                                             {41, 94, 139},
//                                             {93, 54, 142},
//                                             {95, 114, 146},
//                                             {49, 91, 150},
//                                             {92, 62, 154},
//                                             {90, 108, 158},
//                                             {56, 89, 161},
//                                             {90, 69, 165},
//                                             {85, 102, 169},
//                                             {64, 88, 172},
//                                             {87, 76, 176},
//                                             {81, 96, 180},
//                                             {71, 88, 184},
//                                             {83, 83, 188}};

// // WORKS GOOD
// double large_sphere[101][N_AXIS] = {{75, 75, 0},
//                                     {86, 84, 2},
//                                     {77, 97, 4},
//                                     {60, 97, 6},
//                                     {47, 87, 8},
//                                     {43, 71, 10},
//                                     {47, 54, 11},
//                                     {59, 42, 13},
//                                     {75, 37, 14},
//                                     {92, 40, 16},
//                                     {106, 49, 17},
//                                     {115, 64, 18},
//                                     {117, 81, 19},
//                                     {113, 97, 21},
//                                     {102, 110, 22},
//                                     {88, 119, 23},
//                                     {71, 121, 24},
//                                     {54, 118, 25},
//                                     {40, 108, 26},
//                                     {30, 94, 27},
//                                     {25, 78, 28},
//                                     {27, 61, 29},
//                                     {34, 46, 30},
//                                     {45, 33, 31},
//                                     {60, 26, 32},
//                                     {77, 23, 33},
//                                     {94, 26, 34},
//                                     {109, 35, 35},
//                                     {120, 47, 36},
//                                     {127, 63, 37},
//                                     {128, 80, 38},
//                                     {124, 97, 39},
//                                     {115, 111, 40},
//                                     {103, 122, 41},
//                                     {87, 129, 42},
//                                     {70, 130, 43},
//                                     {53, 126, 44},
//                                     {39, 118, 45},
//                                     {27, 105, 46},
//                                     {20, 89, 47},
//                                     {18, 72, 48},
//                                     {22, 56, 49},
//                                     {30, 41, 49},
//                                     {42, 29, 50},
//                                     {57, 21, 51},
//                                     {74, 18, 52},
//                                     {91, 20, 53},
//                                     {106, 28, 54},
//                                     {119, 39, 55},
//                                     {127, 54, 56},
//                                     {131, 70, 57},
//                                     {130, 87, 58},
//                                     {124, 103, 59},
//                                     {114, 116, 59},
//                                     {100, 126, 60},
//                                     {84, 131, 61},
//                                     {67, 131, 62},
//                                     {50, 126, 63},
//                                     {36, 117, 64},
//                                     {26, 103, 65},
//                                     {20, 87, 66},
//                                     {19, 70, 67},
//                                     {23, 54, 68},
//                                     {32, 39, 69},
//                                     {45, 28, 70},
//                                     {60, 22, 70},
//                                     {77, 20, 71},
//                                     {94, 24, 72},
//                                     {108, 32, 73},
//                                     {120, 45, 74},
//                                     {127, 60, 75},
//                                     {128, 77, 76},
//                                     {124, 94, 77},
//                                     {116, 108, 78},
//                                     {103, 119, 79},
//                                     {87, 126, 80},
//                                     {70, 126, 81},
//                                     {54, 122, 82},
//                                     {40, 112, 83},
//                                     {30, 98, 84},
//                                     {25, 82, 85},
//                                     {27, 65, 86},
//                                     {34, 49, 87},
//                                     {46, 37, 88},
//                                     {61, 30, 89},
//                                     {78, 29, 90},
//                                     {94, 34, 92},
//                                     {107, 45, 93},
//                                     {115, 60, 94},
//                                     {117, 77, 95},
//                                     {112, 93, 96},
//                                     {101, 105, 98},
//                                     {85, 112, 99},
//                                     {68, 112, 100},
//                                     {53, 103, 102},
//                                     {44, 89, 103},
//                                     {44, 72, 105},
//                                     {52, 58, 106},
//                                     {67, 51, 108},
//                                     {83, 57, 111},
//                                     {84, 72, 113}};

// WORKS GREAT - captured
unsigned int test_spiral[117][N_AXIS] = {{75, 75, 0},
                                         {84, 83, 1},
                                         {75, 92, 3},
                                         {62, 90, 5},
                                         {53, 80, 6},
                                         {52, 67, 7},
                                         {59, 55, 8},
                                         {70, 48, 9},
                                         {83, 48, 10},
                                         {95, 53, 11},
                                         {104, 64, 12},
                                         {107, 77, 13},
                                         {104, 90, 14},
                                         {96, 101, 15},
                                         {85, 108, 15},
                                         {72, 109, 16},
                                         {59, 106, 17},
                                         {48, 98, 18},
                                         {41, 87, 19},
                                         {38, 74, 19},
                                         {41, 61, 20},
                                         {48, 49, 21},
                                         {58, 41, 22},
                                         {71, 36, 22},
                                         {84, 37, 23},
                                         {97, 42, 24},
                                         {107, 50, 24},
                                         {113, 62, 25},
                                         {116, 75, 26},
                                         {114, 89, 26},
                                         {108, 100, 27},
                                         {98, 110, 28},
                                         {86, 115, 28},
                                         {73, 117, 29},
                                         {59, 114, 30},
                                         {48, 108, 30},
                                         {39, 98, 31},
                                         {33, 85, 32},
                                         {32, 72, 32},
                                         {35, 59, 33},
                                         {42, 47, 34},
                                         {52, 38, 34},
                                         {64, 33, 35},
                                         {77, 31, 35},
                                         {91, 34, 36},
                                         {102, 40, 37},
                                         {112, 50, 37},
                                         {118, 62, 38},
                                         {120, 75, 39},
                                         {118, 88, 39},
                                         {112, 100, 40},
                                         {103, 110, 40},
                                         {91, 117, 41},
                                         {78, 120, 42},
                                         {65, 119, 42},
                                         {52, 114, 43},
                                         {42, 105, 44},
                                         {34, 94, 44},
                                         {31, 81, 45},
                                         {31, 68, 45},
                                         {35, 55, 46},
                                         {43, 44, 47},
                                         {54, 36, 47},
                                         {66, 31, 48},
                                         {80, 30, 48},
                                         {93, 34, 49},
                                         {104, 41, 50},
                                         {113, 51, 50},
                                         {118, 63, 51},
                                         {120, 77, 51},
                                         {117, 90, 52},
                                         {111, 102, 53},
                                         {101, 111, 53},
                                         {89, 117, 54},
                                         {76, 119, 55},
                                         {63, 117, 55},
                                         {51, 111, 56},
                                         {41, 102, 57},
                                         {35, 90, 57},
                                         {32, 77, 58},
                                         {34, 63, 58},
                                         {40, 51, 59},
                                         {49, 41, 60},
                                         {61, 35, 60},
                                         {74, 33, 61},
                                         {87, 35, 62},
                                         {99, 41, 62},
                                         {109, 51, 63},
                                         {114, 63, 64},
                                         {116, 76, 64},
                                         {113, 89, 65},
                                         {106, 101, 66},
                                         {95, 109, 66},
                                         {83, 113, 67},
                                         {69, 113, 68},
                                         {57, 109, 69},
                                         {46, 100, 69},
                                         {40, 88, 70},
                                         {38, 75, 71},
                                         {41, 62, 71},
                                         {49, 51, 72},
                                         {60, 43, 73},
                                         {73, 40, 74},
                                         {86, 43, 75},
                                         {98, 51, 75},
                                         {105, 62, 76},
                                         {107, 75, 77},
                                         {103, 88, 78},
                                         {94, 98, 79},
                                         {82, 103, 80},
                                         {68, 101, 81},
                                         {57, 94, 82},
                                         {52, 82, 83},
                                         {54, 68, 84},
                                         {64, 59, 85},
                                         {77, 59, 87},
                                         {84, 69, 89}};

unsigned int tri_test[51][N_AXIS] = {{82, 84, 0},
                                     {75, 87, 2},
                                     {75, 79, 3},
                                     {86, 84, 5},
                                     {72, 90, 6},
                                     {74, 75, 8},
                                     {90, 86, 9},
                                     {68, 93, 11},
                                     {73, 70, 12},
                                     {94, 88, 14},
                                     {64, 96, 15},
                                     {73, 66, 17},
                                     {98, 91, 18},
                                     {60, 98, 20},
                                     {73, 61, 21},
                                     {102, 94, 23},
                                     {55, 99, 24},
                                     {74, 56, 26},
                                     {105, 98, 27},
                                     {50, 100, 29},
                                     {76, 52, 30},
                                     {108, 102, 32},
                                     {45, 100, 33},
                                     {78, 47, 35},
                                     {110, 107, 36},
                                     {40, 100, 38},
                                     {81, 43, 39},
                                     {105, 106, 41},
                                     {43, 96, 42},
                                     {83, 48, 44},
                                     {100, 105, 45},
                                     {47, 92, 47},
                                     {85, 53, 48},
                                     {95, 103, 50},
                                     {51, 89, 51},
                                     {85, 58, 53},
                                     {91, 101, 54},
                                     {55, 86, 56},
                                     {86, 62, 57},
                                     {87, 98, 59},
                                     {59, 84, 60},
                                     {85, 67, 62},
                                     {84, 95, 63},
                                     {64, 83, 65},
                                     {84, 72, 66},
                                     {81, 91, 68},
                                     {68, 83, 69},
                                     {82, 76, 71},
                                     {79, 87, 72},
                                     {73, 83, 74},
                                     {80, 80, 75}};
Drawing drawings[2] = {Drawing(test_spiral, 117), Drawing(tri_test, 51)};
// Drawing drawings[1] = {Drawing(test_spiral, 240)}; //DOES NOT WORK
// TODO: change the drawings location - the hold too much memory and affect the stack!!!
