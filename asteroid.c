/**
    @file asteroid.c
    @author Ben Fisher
    
    Definitions for functions related to creating, drawing, and
    freeing an asteroid.
*/
#include "asteroid.h"
#include "util.h"
#include <math.h>
#define BIG_MIN_AST_RAD 30
#define BIG_MAX_AST_RAD 100
#define MEDIUM_MIN_AST_RAD 15
#define MEDIUM_MAX_AST_RAD 50
#define SMALL_MIN_AST_RAD 10
#define SMALL_MAX_AST_RAD 25
#define PI 3.14

Asteroid *createAsteroid(int x, int y, float direction, float velocity, AsteroidSize size) {
    Color white = {.r = 255, .g = 255, .b = 255};
    Asteroid *asteroid = (Asteroid *) malloc(sizeof(Asteroid));
    int ptNum = 11;
    Point *points = (Point *) malloc(sizeof(Point) * ptNum);
    //defining asteroid's random shape
    int minRadius, maxRadius;
    switch(size) {
        case big:
            minRadius = BIG_MIN_AST_RAD;
            maxRadius = BIG_MAX_AST_RAD;
            break;
        case medium:
            minRadius = MEDIUM_MIN_AST_RAD;
            maxRadius = MEDIUM_MAX_AST_RAD;
            break;
        case small:
            minRadius = SMALL_MIN_AST_RAD;
            maxRadius = SMALL_MAX_AST_RAD;
            break;
    }

    float thetaDelta = 2 * PI / (ptNum - 1);
    float theta = 0;
    float radius;

    for(int i = 0; i < ptNum - 1; i++) {
        radius = randInt(minRadius, maxRadius);
        points[i].x = radius * cos(theta);
        points[i].y = radius * sin(theta);
        theta += thetaDelta;
    }
    points[ptNum - 1].x = points[0].x;
    points[ptNum - 1].y = points[0].y;
    
    /*
    for(int i = 0; i < ptNum; i++){
        points[i].x *= .5;
        points[i].y *= .5;
    }
    */
    
    fillObject( (Object *) asteroid, x, y, points, ptNum, velocity, direction, white);
    asteroid->size = size;
    return asteroid;
}


void drawAsteroid(Asteroid *asteroid, SDL_Surface* screen) {
    drawObject( (Object *) asteroid, screen );
    
    //draw fire
}
void freeAsteroid(Asteroid *asteroid) {
    freeObject( (Object *) asteroid );
}


bool pointRoughlyNearAsteroid(Point point, Asteroid *asteroid) {
    int maxRadius;
    
    switch(asteroid->size) {
        case big:
            maxRadius = BIG_MAX_AST_RAD;
            break;
        case medium:
            maxRadius = MEDIUM_MAX_AST_RAD;
            break;
        case small:
            maxRadius = SMALL_MAX_AST_RAD;
            break;
    }
    return dist(point.x, point.y, asteroid->center.x, asteroid->center.y) <= maxRadius;
}

bool isBulletInsideAsteroid(Bullet *bullet, Asteroid *asteroid) {
    Point point = bullet->center;
    if( pointRoughlyNearAsteroid(point, asteroid) ) {
        //through line, line through the center of the asteroid
        float cx = point.x;
        float cy = point.y;
        float px = asteroid->points[0].x + asteroid->center.x;
        float py = asteroid->points[0].y + asteroid->center.y;
        float x, y;
        int intersections;
        //cycles through different degrees of ray to see if it can find one with odd intersection count
        for(float theta = bullet->direction; theta < 2*PI + bullet->direction; theta += PI/180){
            //find intersection count by addding intersections from polygon and ray
            //ray's origin is at point and is pointing at theta
            intersections = 0;
            for(int i = 1; i < asteroid->pointNum; i++) {
                x = asteroid->points[i].x + asteroid->center.x;
                y = asteroid->points[i].y + asteroid->center.y;

                    if(doLineSegAndRayIntersect(x, y, px, py, cx, cy, asteroid->center.x + cos(theta), asteroid->center.y + sin(theta))){
                        intersections++;
                    }
                px = x;
                py = y;
            }
            //if there is an odd number of intersections, the bullet is inside the asteroid
            if(intersections % 2 == 1){
                return true;
            }
        }
        return false;
    }
    return false;
}

Asteroid *makeChildAsteroid(Asteroid *asteroid, float direction, float velocity){
    AsteroidSize size;
        switch(asteroid->size){
            case big:
                size = medium;
            break;
            case medium:
                size = small;
            default:
                break;
        }
    return createAsteroid(asteroid->center.x, asteroid->center.y, direction, velocity, size);
}