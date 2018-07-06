/**
    @file ship.c
    @author Ben Fisher
    
    Definitions for functions related to creating, drawing, and
    freeing a ship.
*/
#include "ship.h"
#include "bullet.h"

Ship *createShip(int x, int y, float velocity) {
    Color white = {.r = 255, .g = 255, .b = 255};
    Ship *ship = (Ship *) malloc(sizeof(Ship));
    Object *fire = (Object *) malloc(sizeof(Object));
    Point *firePoints = (Point *) malloc(sizeof(Point) * 2);
    fillObject( fire, x, y, firePoints, 2, 10.0, 0.0, white);
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
    //scaling the ship down to half size
    for(int i = 0; i < ptNum; i++){
        points[i].x *= .5;
        points[i].y *= .5;
    }
    
    fillObject( (Object *) ship, x, y, points, ptNum, 10.0, 3.14/2, white);
    ship->lives = 3;
    //ship->fireTimer = clock();
    ship->fire = fire;
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
    
    //draw fire
}
void freeShip(Ship *ship) {
    freeObject(ship->fire);
    free(ship->points);
    free(ship);
}
