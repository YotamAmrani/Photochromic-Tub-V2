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
Drawing drawings[2] = {Drawing(testing, 25), Drawing(triangle_spiral, 87)};