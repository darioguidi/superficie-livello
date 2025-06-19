#ifndef FUNCTION_H
#define FUNCTION_H

#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>

#define SIZE_W 600

typedef struct {
    float x;
    float y;
    float z;
    Point *nextPoint;
} Point;

void addNoe(Point *point);
void deleteNode(Point *point);
void readFileCSV();

#endif
