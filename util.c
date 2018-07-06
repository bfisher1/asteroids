/**
    @file util.c
    @author Ben Fisher

    Implementation file containing definitions for miscellaneous functions,
    such as generating random integers and delaying the program.
*/
#include "util.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

int randInt(int min, int max){
    return rand() % (max - min) + min;
}

void delayMs(float delay) {
    clock_t start = clock();
    while ( 1000.0 * ((float) (clock() - start)) / CLOCKS_PER_SEC <= delay );
}

float dist(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt( dx * dx + dy * dy );
}

void pacmanBounds(float *x, float *y, int width, int height, int boundary){
    if(*x < -boundary){
        *x = width;
    }
    if(*x > width + boundary){
        *x = 0;
    }
    if(*y < -boundary){
        *y = height;
    }
    if(*y > height + boundary){
        *y = 0;
    }
}