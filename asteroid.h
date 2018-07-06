/**
    @file asteroid.h
    @author Ben Fisher

    Defines the asteroid structure and functions dealing with it.
    Asteroid is an object in space that the drifts about at a
    constant direction and velocity. Asteroids come in 3 sizes
    and are destroyed when hit by a bullet.
*/
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

/**
    Creates an asteroid at the given location with the given
    size, direction and velocity.

    @param x the x coordinate the asteroid is created at
    @param y the y coordinate the asteroid is created at
    @param direction the asteroid's heading
    @param velocity the asteroid's velocity
    @param size the asteroid's size

    @return asteroid described by the given parameters
*/
Asteroid *createAsteroid(int x, int y, float direction, float velocity, AsteroidSize size);

/**
    Draws the asteroid to the surface.

    @param asteroid the asteroid being drawn
    @param screen the screen the asteroid is drawn to
*/
void drawAsteroid(Asteroid *asteroid, SDL_Surface* screen);

/**
    Frees an asteroid from memory.

    @param asteroid the asteroid being freed
*/
void freeAsteroid(Asteroid *asteroid);

#endif /* ASTEROID_H */