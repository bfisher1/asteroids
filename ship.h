
#ifndef SHIP_H
#define SHIP_H
#include <time.h>
#include "object.h"
#include <SDL/SDL.h>
#include "graphics.h"
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
    float fireTimerMs;
    clock_t lastFire;
    Object *fire;
    float bulletTimerMs;
    clock_t lastBullet;
} Ship;

Ship *createShip(int x, int y, float velocity);
void drawShip(Ship *ship, SDL_Surface* screen);
void freeShip(Ship *ship);
Point shipTip(Ship *ship);
#endif /* SHIP_H */
