#include "Drawings.h"

double testing[25][N_AXIS] = {{35.17, 38.75, 0},
                              {31.58, 39.78, 1.44},
                              {28.64, 40.14, 2.87},
                              {29.54, 36.52, 4.31},
                              {31, 34.7, 5.6},
                              {33.85, 37.35, 6.53},
                              {36.7, 40.01, 7.46},
                              {36.7, 41.6, 8.32},
                              {32.77, 41.74, 9.07},
                              {28.85, 41.87, 9.83},
                              {24.92, 42.01, 10.59},
                              {26.15, 38.93, 11.34},
                              {27.99, 35.46, 12.1},
                              {29.84, 31.99, 12.85},
                              {31.73, 31.04, 13.54},
                              {33.7, 34.48, 14.11},
                              {35.67, 37.91, 14.68},
                              {37.64, 41.35, 15.26},
                              {39.61, 44.78, 15.83},
                              {37.49, 45.24, 16.36},
                              {33.61, 44.41, 16.86},
                              {29.73, 43.59, 17.37},
                              {25.85, 42.76, 17.88},
                              {21.97, 41.94, 18.39},
                              {21.09, 40.14, 18.9}};

double triangle_spiral[87][N_AXIS] = {{61.42, 79.17, 0},
                                      {60.33, 71.45, 1.5},
                                      {67.56, 74.37, 3},
                                      {56.63, 68.75, 4.5},
                                      {71.75, 72.52, 6},
                                      {60.93, 83.73, 7.5},
                                      {75.44, 69.51, 9},
                                      {61.69, 88.43, 10.5},
                                      {52.18, 67.06, 12},
                                      {63.73, 92.99, 13.5},
                                      {47.21, 66.55, 15},
                                      {78.37, 65.46, 16.5},
                                      {41.96, 67.3, 18},
                                      {80.34, 60.54, 19.5},
                                      {67.01, 97.16, 21},
                                      {81.17, 54.94, 22.5},
                                      {71.45, 100.68, 24},
                                      {36.69, 69.39, 25.5},
                                      {76.91, 103.31, 27},
                                      {31.68, 72.8, 28.5},
                                      {80.72, 48.89, 30},
                                      {27.19, 77.51, 31.5},
                                      {78.88, 42.64, 33},
                                      {83.23, 104.85, 34.5},
                                      {75.62, 36.48, 36},
                                      {90.2, 105.1, 37.5},
                                      {23.49, 83.42, 39},
                                      {97.57, 103.93, 40.5},
                                      {20.82, 90.39, 42},
                                      {70.92, 30.68, 43.5},
                                      {19.4, 98.24, 45},
                                      {64.83, 25.53, 46.5},
                                      {105.08, 101.23, 48},
                                      {57.46, 21.3, 49.5},
                                      {112.43, 96.96, 51},
                                      {19.42, 106.74, 52.5},
                                      {119.34, 91.12, 54},
                                      {21.02, 115.64, 55.5},
                                      {48.95, 18.24, 57},
                                      {24.32, 124.64, 58.5},
                                      {39.5, 16.59, 60},
                                      {125.49, 83.77, 61.5},
                                      {29.35, 16.54, 63},
                                      {130.6, 75, 64.5},
                                      {29.35, 133.46, 66},
                                      {125.49, 66.23, 67.5},
                                      {39.5, 133.41, 69},
                                      {24.32, 25.36, 70.5},
                                      {48.95, 131.76, 72},
                                      {21.02, 34.36, 73.5},
                                      {119.34, 58.88, 75},
                                      {19.42, 43.26, 76.5},
                                      {112.43, 53.04, 78},
                                      {57.46, 128.7, 79.5},
                                      {105.08, 48.77, 81},
                                      {64.83, 124.47, 82.5},
                                      {19.4, 51.76, 84},
                                      {70.92, 119.32, 85.5},
                                      {20.82, 59.61, 87},
                                      {97.57, 46.07, 88.5},
                                      {23.49, 66.58, 90},
                                      {90.2, 44.9, 91.5},
                                      {75.62, 113.52, 93},
                                      {83.23, 45.15, 94.5},
                                      {78.88, 107.36, 96},
                                      {27.19, 72.49, 97.5},
                                      {80.72, 101.11, 99},
                                      {31.68, 77.2, 100.5},
                                      {76.91, 46.69, 102},
                                      {36.69, 80.61, 103.5},
                                      {71.45, 49.32, 105},
                                      {81.17, 95.06, 106.5},
                                      {67.01, 52.84, 108},
                                      {80.34, 89.46, 109.5},
                                      {41.96, 82.7, 111},
                                      {78.37, 84.54, 112.5},
                                      {47.21, 83.45, 114},
                                      {63.73, 57.01, 115.5},
                                      {52.18, 82.94, 117},
                                      {61.69, 61.57, 118.5},
                                      {75.44, 80.49, 120},
                                      {60.93, 66.27, 121.5},
                                      {71.75, 77.48, 123},
                                      {56.63, 81.25, 124.5},
                                      {67.56, 75.63, 126},
                                      {60.33, 78.55, 127.5},
                                      {61.42, 70.83, 129}};

double simple_spiral[101][N_AXIS] = {{74.52, 75, 0},
                                     {88.68, 85.74, 2.35},
                                     {77.33, 101.24, 5.3},
                                     {57.49, 101.63, 7.75},
                                     {41.96, 88.99, 9.91},
                                     {36.39, 69.66, 11.89},
                                     {41.77, 50.22, 13.73},
                                     {56, 35.87, 15.47},
                                     {75.29, 29.76, 17.14},
                                     {95.3, 32.85, 18.74},
                                     {112.09, 44.22, 20.28},
                                     {122.68, 61.53, 21.78},
                                     {125.41, 81.64, 23.24},
                                     {120.05, 101.22, 24.66},
                                     {107.59, 117.26, 26.05},
                                     {90.02, 127.47, 27.42},
                                     {69.92, 130.5, 28.76},
                                     {50.08, 126.05, 30.08},
                                     {33.11, 114.83, 31.37},
                                     {21.16, 98.37, 32.65},
                                     {15.63, 78.79, 33.92},
                                     {17.12, 58.49, 35.16},
                                     {25.39, 39.89, 36.4},
                                     {39.39, 25.12, 37.62},
                                     {57.48, 15.79, 38.83},
                                     {77.64, 12.91, 40.02},
                                     {97.64, 16.72, 41.21},
                                     {115.35, 26.78, 42.39},
                                     {128.93, 41.96, 43.56},
                                     {137, 60.66, 44.72},
                                     {138.75, 80.96, 45.87},
                                     {134.07, 100.79, 47.01},
                                     {123.46, 118.18, 48.15},
                                     {107.98, 131.43, 49.29},
                                     {89.17, 139.26, 50.41},
                                     {68.86, 140.96, 51.54},
                                     {49, 136.39, 52.65},
                                     {31.48, 125.99, 53.77},
                                     {17.92, 110.78, 54.87},
                                     {9.58, 92.18, 55.98},
                                     {7.22, 71.94, 57.08},
                                     {11.05, 51.92, 58.18},
                                     {20.68, 33.96, 59.28},
                                     {35.24, 19.69, 60.37},
                                     {53.39, 10.42, 61.46},
                                     {73.48, 6.95, 62.55},
                                     {93.69, 9.61, 63.64},
                                     {112.2, 18.15, 64.73},
                                     {127.35, 31.79, 65.82},
                                     {137.79, 49.3, 66.9},
                                     {142.56, 69.12, 67.99},
                                     {141.27, 89.46, 69.07},
                                     {134, 108.5, 70.16},
                                     {121.43, 124.55, 71.24},
                                     {104.67, 136.15, 72.33},
                                     {85.22, 142.26, 73.42},
                                     {64.84, 142.32, 74.51},
                                     {45.36, 136.32, 75.6},
                                     {28.55, 124.8, 76.69},
                                     {15.93, 108.79, 77.79},
                                     {8.68, 89.74, 78.89},
                                     {7.47, 69.4, 79.99},
                                     {12.42, 49.63, 81.09},
                                     {23.09, 32.26, 82.2},
                                     {38.51, 18.94, 83.31},
                                     {57.25, 10.92, 84.42},
                                     {77.53, 8.98, 85.54},
                                     {97.44, 13.34, 86.66},
                                     {115.04, 23.6, 87.79},
                                     {128.63, 38.78, 88.93},
                                     {136.83, 57.43, 90.07},
                                     {138.8, 77.71, 91.22},
                                     {134.31, 97.58, 92.37},
                                     {123.78, 115.01, 93.54},
                                     {108.25, 128.19, 94.71},
                                     {89.32, 135.69, 95.89},
                                     {68.98, 136.69, 97.08},
                                     {49.43, 131, 98.28},
                                     {32.84, 119.21, 99.5},
                                     {21.11, 102.57, 100.72},
                                     {15.63, 82.97, 101.96},
                                     {17.13, 62.68, 103.22},
                                     {25.5, 44.14, 104.49},
                                     {39.8, 29.67, 105.77},
                                     {58.28, 21.17, 107.08},
                                     {78.57, 19.87, 108.41},
                                     {97.94, 26.03, 109.76},
                                     {113.63, 38.94, 111.13},
                                     {123.27, 56.81, 112.54},
                                     {125.26, 77.02, 113.98},
                                     {119.08, 96.35, 115.45},
                                     {105.58, 111.48, 116.97},
                                     {87, 119.56, 118.54},
                                     {66.77, 118.76, 120.16},
                                     {49.1, 108.92, 121.86},
                                     {38.23, 91.9, 123.64},
                                     {37.39, 71.77, 125.53},
                                     {47.53, 54.44, 127.58},
                                     {65.92, 46.65, 129.84},
                                     {84.28, 53.73, 132.47},
                                     {85.55, 71.99, 135.64}};

Drawing drawings[3] = {Drawing(testing, 25), Drawing(triangle_spiral, 87), Drawing(simple_spiral, 100)};
