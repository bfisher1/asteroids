
#ifndef ASTEROID_H
#define ASTEROID_H
#include "object.h"
#include <SDL/SDL.h>
#include "graphics.h"
/**
    Enumeration for asteroid sizes.
*/
typedef enum {
    big,
    medium,
    small
} AsteroidSize;

/**
    Structure for an asteroid. 'Extends' object.
*/
typedef struct {
    int pointNum;
    Point *points;
    Point center;
    float velocity;
    float direction;
    float orientation;
    Color color;
    AsteroidSize size;
} Asteroid;
#endif /* ASTEROID_H */