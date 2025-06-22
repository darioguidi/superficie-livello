#ifndef FUNCTION_H
#define FUNCTION_H

#define SDL_MAIN_HANDLED

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>

// Constant
#define SIZE_W 600
#define SIZE_POINT 3
#define SIZE_GRID 250
#define OFFSET_X (SIZE_W / 2)
#define OFFSET_Y (SIZE_W / 2)
#define DISTANCE 500
#define MAX_POINTS (SIZE_GRID * SIZE_GRID)

// Struct
typedef struct {
    float x;
    float y;
    float z;
} Point;

// Function
void createFileCSV();
void readFileCSV(Point *sup);
void generatePlane(Point *plane);

void printPoint(SDL_Renderer *renderer, Point point);
void printPointPlane(SDL_Renderer *renderer, Point point);

void printPointsSuperficie(SDL_Renderer *renderer, Point *sup);
void printPointsPiano(SDL_Renderer *renderer, Point *plane);

#endif
