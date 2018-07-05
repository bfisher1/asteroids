/**
    @file object.h
    @author Ben Fisher

    Contains declarations for functions involved with space objects.
    These are objects defined by a set of points, velocity, and
    direction. They also can choose their drawing functions.
*/
#include <stdbool.h>
#include <SDL/SDL.h>
#include "graphics.h"

#ifndef OBJECT_H
#define OBJECT_H

/**
    Structure for a cartesian point.
*/
typedef struct {
    float x;
    float y;
} Point;

/**
    Structure for a polar point, defined by radius and degrees.
*/
typedef struct {
    int radius;
    float angle;
} PolarPoint;



/**
    Structure for a space object. The points in points are all
    relative to the center point.
*/
typedef struct ObjectTag {
    int pointNum;
    Point *points;
    Point center;
    float velocity;
    float direction;
    float orientation;
    Color color;
} Object;

/**
    Fills the fields of an object. Like an abstract class, Objects
    are never constructed. Rather, they are implemented by the
    structures that extend them (asteroid, ship, etc). For instance,
    an asteroid would be cast to an object and passed to this
    function in order to fill in its object related fields.

    @param object the object having its fields filled
    @param x the x coordinate of the center
    @param y the y coordinate of the center
    @param points the list of points
    @param ptNum the number of points in the points list
    @param velocity the velocity of the object
    @param direction the direction the object is moving
    @param color the color of the object
    
    @return object with the given fields
*/
void fillObject( Object *object, int x, int y, Point *points, int ptNum, float velocity, float direction, Color color );

/**
    Draws an object to a screen as a polygon defined by points.

    @param object the object being drawn
    @param screen the screen the object is being drawn to
*/
void drawObject(Object *object, SDL_Surface* screen);

/**
    Moves an object forward according to its velocity and direction.

    @param object the object being moved
    @param sceen the screen the object is moving on
*/
void forwardObject(Object *object, SDL_Surface* screen);

/**
    Reverses an object according to its velocity and direction.

    @param object the object being moved
    @param sceen the screen the object is moving on
*/
void reverseObject(Object *object, SDL_Surface* screen);

/**
    Rotates an object by the given radians.

    @param object the object being rotated
    @param radians the amount the object is beng rotated by
*/
void rotateObject(Object *object, float radians);

/**
    Determines if a point is in the object.

    @param point the point that may be inside the object
    @param object the object that may have a point in it
*/
bool isPtInObject(Point *point, Object (object));

/**
    Frees an object from memory.

    @param object the object being freed
*/
void freeObject(Object *object);
#endif /* OBJECT_H */