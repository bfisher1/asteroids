/**
    @file bullet.c
    @author Ben Fisher

    Declares functions related to the bullet structure.
*/
#include "bullet.h"
#include <math.h>
#include "util.h"

Bullet *createBullet(int x, int y, float direction, float velocity, int range, int radius, Color color){
    Bullet *bullet = (Bullet *) malloc(sizeof(Bullet));
    bullet->center.x = x;
    bullet->center.y = y;
    bullet->direction = direction;
    bullet->velocity = velocity;
    bullet->range = range;
    bullet->radius = radius;
    bullet->distCovered = 0;
    bullet->color = color;
    return bullet;
}

void drawBullet(Bullet *bullet, SDL_Surface* screen) {
    for(int i =1; i < bullet->radius; i++){
            drawCircle(screen, bullet->center.x, bullet->center.y, i, bullet->color);
        }
}

void moveBullet(Bullet *bullet, SDL_Surface* screen) {
    float nx = bullet->velocity * cos(bullet->direction);
    float ny = bullet->velocity * sin(bullet->direction);
    bullet->distCovered += dist(0, 0, nx, ny);
    bullet->center.x += nx;
    bullet->center.y += ny;
}

bool hasCoveredDist(Bullet *bullet){
    return bullet->distCovered >= bullet->range;
}

void freeBullet(Bullet *bullet) {
    free(bullet);
}