/**
    @file asteroid.c
    @author Ben Fisher
    
    Definitions for functions related to creating, drawing, and
    freeing an asteroid.
*/
#include "asteroid.h"
#include "util.h"
#include <math.h>
#define BIG_MIN_AST_RAD 30
#define BIG_MAX_AST_RAD 100
#define MEDIUM_MIN_AST_RAD 75
#define MEDIUM_MAX_AST_RAD 150
#define SMALL_MIN_AST_RAD 100
#define SMALL_MAX_AST_RAD 200
#define PI 3.14

Asteroid *createAsteroid(int x, int y, float direction, float velocity, AsteroidSize size) {
    Color white = {.r = 255, .g = 255, .b = 255};
    Asteroid *asteroid = (Asteroid *) malloc(sizeof(Asteroid));
    int ptNum = 11;
    Point *points = (Point *) malloc(sizeof(Point) * ptNum);
    //defining asteroid's random shape
    int minRadius, maxRadius;
    switch(size) {
        case big:
            minRadius = BIG_MIN_AST_RAD;
            maxRadius = BIG_MAX_AST_RAD;
            break;
        case medium:
            minRadius = MEDIUM_MIN_AST_RAD;
            maxRadius = MEDIUM_MAX_AST_RAD;
            break;
        case small:
            minRadius = SMALL_MIN_AST_RAD;
            maxRadius = SMALL_MAX_AST_RAD;
            break;
    }

    float thetaDelta = 2 * PI / (ptNum - 1);
    float theta = 0;
    float radius;

    for(int i = 0; i < ptNum - 1; i++) {
        radius = randInt(minRadius, maxRadius);
        points[i].x = radius * cos(theta);
        points[i].y = radius * sin(theta);
        theta += thetaDelta;
    }
    points[ptNum - 1].x = points[0].x;
    points[ptNum - 1].y = points[0].y;
    
    /*
    for(int i = 0; i < ptNum; i++){
        points[i].x *= .5;
        points[i].y *= .5;
    }
    */
    
    fillObject( (Object *) asteroid, x, y, points, ptNum, 10.0, 3.14/2, white);
    asteroid->size = size;
    return asteroid;
}


void drawAsteroid(Asteroid *asteroid, SDL_Surface* screen) {
    drawObject( (Object *) asteroid, screen );
    
    //draw fire
}
void freeAsteroid(Asteroid *asteroid) {
    freeObject( (Object *) asteroid );
}
