/**
    @file ship.h
    @author Ben Fisher

    Defines ship structure and functions dealing with it.
    Ship is an object in space that the user contols.
    It has a number of lives, and animates fire when
    moving. It is destroyed when hit by an asteroid or
    an alien bullet.
*/
#ifndef SHIP_H
#define SHIP_H
#include <time.h>
#include "object.h"
#include <SDL/SDL.h>
#include "graphics.h"
/** The numerator in the chance for the fire to be drawn. ie the 3 in 3/10 */
#define FIRE_FLICKER_CHANCE_NUM 3

/** The denominator in the chance for the fire to be drawn. ie the 10 in 3/10 */
#define FIRE_FLICKER_CHANCE_DEN 10
/**
    Structure for a ship. 'Extends' object.
*/
typedef struct {
    int pointNum;
    Point *points;
    Point center;
    float velocity;
    float direction;
    float orientation;
    Color color;
    int lives;
    Object *fire;
} Ship;

/**
    Creates a ship at the given location.

    @param x the x coordinate the ship is created at
    @param y the y coordinate the ship is created at
    @param velocity the ship's velocity when driven

    @return ship described by the given parameters
*/
Ship *createShip(int x, int y, float velocity);

/**
    Draws the ship to the surface.

    @param ship the ship being drawn
    @param screen the screen the ship is drawn to
*/
void drawShip(Ship *ship, SDL_Surface* screen);

/**
    Frees a ship from memory.

    @param ship the ship being freed
*/
void freeShip(Ship *ship);

/**
    Returns the global point where the ship's tip is.
    Used for finding out where bullets start.

    @param ship the ship in question
    
    @return the point where the ship's tip is
*/
Point shipTip(Ship *ship);

/**
    Animates the ship's fire by only drawing it randomly.
    The chance to draw it is determined by the FIRE_FLICKER_CHANCE
    macros.

    @param ship the ship whose fire is being drawn
    @param screen the screen the fire is being animated on
*/
void animateShipFire(Ship *ship, SDL_Surface* screen);

/**
    Moves the ship across the screen, according to its velocity and
    direction.

    @param ship the ship being moved
    @param screen the screen the ship is being moved across
*/
void moveShip(Ship *ship, SDL_Surface* screen);

/**
    Turns the ship by the given amount.

    @param ship the ship being turned
    @param radians the amount the ship is turning
*/
void turnShip(Ship *ship, float radians);

#endif /* SHIP_H */
