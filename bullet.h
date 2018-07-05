/**
    @file bullet.h
    @author Ben Fisher

    Defines the structure for a bullet and declares functions used with it.
    Bullets are created at an origin point and move with a constant
    velocity and heading until they have moved past a max distance.
*/
#ifndef BULLET_H
#define BULLET_H
#include <time.h>
#include "object.h"
#include <SDL/SDL.h>
#include "graphics.h"
#include <stdbool.h>

/**
    Structure for a bullet.
*/
typedef struct {
    Point center;
    float velocity;
    float direction;
    Color color;
    int radius;
    int range;
    int distCovered;
} Bullet;

/**
    Creates a bullet that starts at (x,y), heads at the given
    velocity in the given direction, and that dissapears after
    reaching a certain distance from its origin.

    @param x the start x coordinate for the bullet
    @param y the start y coordinate for the bullet
    @param direction the direction the bullet moves in
    @param velocity how quickly the bullet moves
    @param range how far away the bullet travels before it dies
    @param radius how big the bullet is
    @param color the color of the bullet

    @return bullet defined by the given characteristics
*/
Bullet *createBullet(int x, int y, float direction, float velocity, int range, int radius, Color color);

/**
    Draws a bullet to the given screen.

    @param bullet the bullet being drawn
    @param screen the screen the bullet is drawing to
*/
void drawBullet(Bullet *bullet, SDL_Surface* screen);

/**
    Moves a bullet across the given screen until it .

    @param bullet the bullet being moved
    @param screen the screen the bullet moves acrosss
*/
void moveBullet(Bullet *bullet, SDL_Surface* screen);

/**
    Determines if the bullet has covered enough distance from its
    starting point to die.

    @param bullet the bullet being checked
*/
bool hasCoveredDist(Bullet *bullet);

/**
    Frees a bullet from memory.

    @param bullet the bullet being freed
*/
void freeBullet(Bullet *bullet);
#endif /* BULLET_H */
