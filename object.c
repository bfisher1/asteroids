/**
    @file object.c
    @author Ben Fisher

    Contains definitions for functions involved with space objects.
    An object acts as a super class for things in space like
    asteroids and ships. Objects are basically a set of points
    connected by lines. These points are relative to the center
    point of the object. An object has a direction and velocity
    as well.
*/
#include "object.h"
#include "graphics.h"
#include <stdlib.h>
#include <math.h>
#include "util.h"
#include <stdio.h>
/** Border of the pacman boundaries */
#define BORDER 30
#define PI 3.14

void fillObject(Object *object, int x, int y, Point *points, int ptNum, float velocity, float direction, Color color) {
    object->center.x = x;
    object->center.y = y;
    object->points = points;
    object->pointNum = ptNum;
    object->velocity = velocity;
    object->direction = direction;
    object->color = color;
}

void drawObject(Object *object, SDL_Surface* screen) {
    //center points
    int cx = object->center.x;
    int cy = object->center.y;
    //previous x and y
    int px = object->points->x;
    int py = object->points->y;
    Point *last = object->points + object->pointNum;
    for (Point *pt = object->points + 1; pt < last; pt++) {
        drawLine(screen, cx + px, cy + py, cx + pt->x, cy + pt->y, object->color);
        
        px = pt->x;
        py = pt->y;
    }
}

void forwardObject(Object *object, SDL_Surface* screen) {
    object->center.x +=  object->velocity * cos( object->direction );
    object->center.y +=  object->velocity * sin( object->direction );
    pacmanBounds(&object->center.x, &object->center.y, screen->w, screen->h, BORDER);
    
    
}

void reverseObject(Object *object, SDL_Surface* screen) {
    object->center.x -= object->velocity * cos( object->direction );
    object->center.y -= object->velocity * sin( object->direction );
    pacmanBounds(&object->center.x, &object->center.y, screen->w, screen->h, BORDER);
    
}

void rotateObject(Object *object, float radians) {
    Point *last = object->points + object->pointNum;
    for (Point *pt = object->points; pt < last; pt++) {
        float distance = dist( 0.0, 0.0, pt->x, pt->y );
        //calculate new angle
        float angle = atan2(pt->y, pt->x) + radians;
        //printf( "%f ", distance );
        pt->x = distance * cos( angle );
        pt->y = distance * sin( angle );
    }
    object->orientation += radians;
    //printf( "\n");
}

bool objectsColliding(Object *object1, Object *object2) {
    int px1, py1, px2, py2, x1, y1, x2, y2;
    px1 = object1->points[0].x + object1->center.x;
    py1 = object1->points[0].y + object1->center.y;
    for(int i = 1; i <= object1->pointNum; i++) {
        x1 = object1->points[i % object1->pointNum].x + object1->center.x;
        y1 = object1->points[i % object1->pointNum].y + object1->center.y;
        px2 = object2->points[0].x + object2->center.x;
        py2 = object2->points[0].y + object2->center.y;
        for(int j = 1; j < object2->pointNum; j++) {
            x2 = object2->points[j % object2->pointNum].x + object2->center.x;
            y2 = object2->points[j % object2->pointNum].y + object2->center.y;
            if(lineSegsIntersect(px1, py1, x1, y1, px2, py2, x2, y2)) {
                return true;
            }
            px2 = x2;
            py2 = y2;
        }
        px1 = x1;
        py1 = y1;
    }
    return false;
}

void freeObject(Object *object) {
    free(object->points);
    free(object);
}

void accelerateObject(Object *object, float rate, float maxVelocity) {
    float vx, vy;
    vx = object->velocity * cos(object->direction) + rate * cos(object->orientation);
    vy = object->velocity * sin(object->direction) + rate * sin(object->orientation);
    object->velocity = dist(0, 0, vx, vy);
    if(object->velocity > maxVelocity){
        object->velocity = maxVelocity;
    }
    object->direction = atan2(vy, vx);
}

void decelerateObject(Object *object, float rate) {
    if(object->velocity > 0){
        object->velocity -= rate;
    }
    if(object->velocity < 0){
        object->velocity += rate;
    }
    
}