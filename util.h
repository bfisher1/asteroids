/**
    @file util.h
    @author Ben Fisher

    Header file containing declarations for miscellaneous functions,
    such as generating random integers and delaying the program.
*/
#ifndef UTIL
#define UTIL

/**
    Generates a random integer between min and max.

    @param min the min random number
    @param max the max random number
    
    @return random number between min and max
*/
int randInt(int min, int max);

/**
    Delays the program for the given amount of milliseconds.

    @param delay the time the program should be delayed for
*/
void delayMs(float delay);

/**
    Calculates the distance between 2 points.

    @param x1 the x coordinate of the first point
    @param y1 the y coordinate of the first point
    @param x2 the x coordinate of the second point
    @param y2 the y coordinate of the second point
    
    @return the distance between the 2 points
*/
float dist(float x1, float y1, float x2, float y2);
#endif /* UTIL */