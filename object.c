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

void forwardObject(Object *object) {
    object->center.x +=  object->velocity * cos( object->direction );
    object->center.y +=  object->velocity * sin( object->direction );
}

void reverseObject(Object *object) {
    object->center.x -= object->velocity * cos( object->direction );
    object->center.y -= object->velocity * sin( object->direction );
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
    object->direction += radians;
    //printf( "\n");
}

bool isPtInObject(Point *point, Object (object)) {
    return false;
}

void freeObject(Object *object) {
    free(object->points);
    free(object);
}