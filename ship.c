/**
    @file ship.c
    @author Ben Fisher
    
    Definitions for functions related to creating, drawing, and
    freeing a ship.
*/
#include "ship.h"
#include "bullet.h"
#include "util.h"
#include <math.h>
#define PI 3.14

Ship *createShip(int x, int y, float velocity) {
    Color white = {.r = 255, .g = 255, .b = 255};
    Ship *ship = (Ship *) malloc(sizeof(Ship));
    
    Point *firePoints = (Point *) malloc(sizeof(Point) * 3);
    Object *fire = (Object *) malloc(sizeof(Object));
    float width, height;
    width = 15;
    height = 40;
    //defining the fire's shape
    firePoints[0].x = width;
    firePoints[0].y = height;
    firePoints[1].x = 0;
    firePoints[1].y = 0;
    firePoints[2].x = -width;
    firePoints[2].y = height;

    fillObject( fire, x, y, firePoints, 3, 10.0, 0.0, white);
    int ptNum = 5;
    Point *points = (Point *) malloc(sizeof(Point) * ptNum);
    //defining shape's ship
    points[0].x = -33;
    points[0].y = -40;
    points[1].x = 0;
    points[1].y = 60;
    points[2].x = 33;
    points[2].y = -40;
    points[3].x = 25;
    points[3].y = -16;
    points[4].x = -25;
    points[4].y = -16;
    
    ship->fire = fire;

    float rotation, scale, radius, angle;
    rotation = - PI / 2;
    scale = .5;
    for(int i = 0; i < ptNum; i++){
        //scaling the ship size
        points[i].x *= scale;
        points[i].y *= scale;
        //rotate
        radius = dist(0.0, 0.0, points[i].x, points[i].y);
        angle = atan2(points[i].y, points[i].x) + rotation;
        points[i].x = radius * cos(angle);
        points[i].y = radius * sin(angle);
    }

    float down = 60;
    for(int i = 0; i < ship->fire->pointNum; i++) {
        //shifting the fire down
        ship->fire->points[i].y -= down;
        //scaling the ship size
        ship->fire->points[i].x *= scale;
        ship->fire->points[i].y *= scale;
        //rotate
        radius = dist(0.0, 0.0, ship->fire->points[i].x, ship->fire->points[i].y);
        angle = atan2(ship->fire->points[i].y, ship->fire->points[i].x) + rotation;
        ship->fire->points[i].x = radius * cos(angle);
        ship->fire->points[i].y = radius * sin(angle);
    }
    
    fillObject( (Object *) ship, x, y, points, ptNum, 10.0, 3.14/2, white);
    ship->lives = 3;
    
    ship->velocity = velocity;
    return ship;
}

Point shipTip(Ship *ship) {
    Point p = ship->points[1];
    p.x += ship->center.x;
    p.y += ship->center.y;
    
    return p;
}

void drawShip(Ship *ship, SDL_Surface* screen) {
    drawObject( (Object *) ship, screen );
}

void freeShip(Ship *ship) {
    freeObject(ship->fire);
    free(ship->points);
    free(ship);
}

void animateShipFire(Ship *ship, SDL_Surface* screen){
    if(randInt(0,FIRE_FLICKER_CHANCE_DEN) <= FIRE_FLICKER_CHANCE_NUM) {
        drawObject((Object *) ship->fire, screen);
    }
}
void moveShip(Ship *ship, SDL_Surface* screen) {
    forwardObject((Object *) ship, screen);
    ship->fire->center.x = ship->center.x;
    ship->fire->center.y = ship->center.y;
}

void turnShip(Ship *ship, float radians) {
    rotateObject( (Object *) ship, radians);
    rotateObject( ship->fire, radians);
}