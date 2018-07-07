/**
    @file main.c
    @author Ben Fisher

    The main program for a game of asteroids.
*/
#include <stdio.h>
#include "object.h"
#include <stdbool.h>
#include <stdlib.h>
#include "object.h"
#include "ship.h"
#include "asteroid.h"
#include <SDL/SDL.h>
#include "util.h"
#include "bullet.h"
#include "Queue/queue.h"
#include <time.h>

#define WIDTH 1200
#define HEIGHT 800
#define DEPTH 32
#define SECONDS_BETWEEN_SHOTS .5
#define RESPAWN_DELAY_SECONDS 1.0
#define BULLET_SPEED 15.0
#define SHIP_SPEED 10.0
#define ASTEROID_START_NUM 4
#define ASTEROID_MIN_VEL 3.5
#define ASTEROID_MAX_VEL 4.5
#define PI 3.14
#define REFRESH_RATE .01
#define SHIP_START_X (WIDTH / 2)
#define SHIP_START_Y (HEIGHT / 2)
#define SHIP_TURN_SPEED .1
#define MAX_VELOCTY 11.0
#define SHIP_ACCEL .2
#define SHIP_DECEL .1

/**
    The program's starting point.

    @param argc number of command line arguments
    @param argv the command line arguments

    @return exit status of the program
*/
int main(int argc, char *argv[])
{ 

    printf("%d\n", doLineSegAndRayIntersect(1146, 548, 1203, 548, 604, 560, 604, 548));
    SDL_Surface *screen;
    SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
   
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_RESIZABLE|SDL_HWSURFACE)))
    {
        SDL_Quit();
        return 1;
    }

    time_t t;
    srand((unsigned) time(&t));
    
    Ship *ship = createShip(SHIP_START_X, SHIP_START_Y, 0);
    Color black = {.r = 0, .g = 0, .b = 0};
    Color white = {.r = 255, .g = 255, .b = 255};
    
    bool shipAlive = false;
    
    
    bool up = false;
    //bool down = false;
    bool left = false;
    bool right = false;
    bool gameOver = false;
    Bullet *bullet = NULL;
    Asteroid *asteroid = NULL;
    Queue *asteroids = makeQueue();
    //spawn asteroids
    for(int i = 0; i < ASTEROID_START_NUM; i++){
        enqueue(asteroids, createAsteroid(randInt(0, screen->w), randInt(0, screen->h), randFloat(0.0, 2 * PI), randFloat(ASTEROID_MIN_VEL, ASTEROID_MAX_VEL), big));
    }

    Queue *bullets = makeQueue();
    clock_t lastShot = clock();
    clock_t lastUpdate = clock();
    clock_t lastDeath = clock();
	while(!gameOver) {
        while(SDL_PollEvent(&event)) 
         {      
              switch (event.type) 
              {
                  case SDL_QUIT:
                    gameOver = true;
                    break;
                  case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_LEFT:
                            left = true;
                            break;
                        case SDLK_RIGHT:
                            right = true;
                            break;
                        case SDLK_UP:
                            up = true;
                            break;
                        case SDLK_DOWN:
                            //down = true;
                            break;
                        case SDLK_ESCAPE:
                            gameOver = true;
                            break;
                        case SDLK_SPACE:
                            if( ((float) (clock() - lastShot)) / CLOCKS_PER_SEC >= SECONDS_BETWEEN_SHOTS && shipAlive) {
                                Point tip = shipTip(ship);
                                bullet = createBullet(tip.x, tip.y, ship->orientation, BULLET_SPEED, 600, 3, white);
                                enqueue(bullets, bullet);
                            }
                        default:
                            break;
                    }
                    break;  
                  case SDL_KEYUP:
                    switch(event.key.keysym.sym){
                        case SDLK_LEFT:
                            left = false;
                            break;
                        case SDLK_RIGHT:
                            right = false;
                            break;
                        case SDLK_UP:
                            up = false;
                            break;
                        case SDLK_DOWN:
                            //down = false;
                            break;
                        default:
                            break;
                    }
                    break;
              }
         }
        drawRect(screen, 0, 0, WIDTH, HEIGHT, black);
        if( ( (float) (clock() - lastUpdate)) / CLOCKS_PER_SEC >= REFRESH_RATE ){
            
            if(shipAlive) {
                if(left) {
                turnShip(ship,  -SHIP_TURN_SPEED);
                }
                else if(right) {
                    turnShip(ship, SHIP_TURN_SPEED);
                }
                if(up) {
                    accelerateObject((Object *) ship, SHIP_ACCEL, MAX_VELOCTY);
                } else {
                    decelerateObject((Object *) ship, ship->velocity * .01 );
                }
                
                moveShip(ship, screen);
            }
            
            
            if(!isQueueEmpty(bullets)) {
                for(int i = 0; i < queueSize(bullets); i++){
                    bullet = (Bullet *) dequeue(bullets);
                    moveBullet(bullet, screen);
                    drawBullet(bullet, screen);
                    enqueue(bullets, bullet);
                }

                if( hasCoveredDist((Bullet *) peekFront(bullets)) ){
                    freeBullet((Bullet *) dequeue(bullets));
                }
            }
            
            if(!isQueueEmpty(asteroids)) {
                bool lostLife = false;
                for(int i = 0; i < queueSize(asteroids); i++){
                    asteroid = (Asteroid *) dequeue(asteroids);
                    forwardObject((Object *) asteroid, screen);
                    //Ship has hit an asteroid
                    if( !lostLife && objectsColliding((Object *) asteroid, (Object *) ship) && shipAlive ) {
                        ship->lives--;
                        ship->center.x = SHIP_START_X;
                        ship->center.y = SHIP_START_Y;
                        ship->velocity = 0.0;
                        shipAlive = false;
                        lastDeath = clock();
                    }
                    drawAsteroid(asteroid, screen);
                    enqueue(asteroids, asteroid);
                }
            } else {
                gameOver = true;
            }

            if(!isQueueEmpty(bullets) && !isQueueEmpty(asteroids)) {
                for(int i = 0; i < queueSize(bullets); i++){
                    bullet = (Bullet *) dequeue(bullets);
                    bool oneDown = false;
                    for(int j = 0; j < queueSize(asteroids) && !oneDown; j++){
                        asteroid = (Asteroid *) dequeue(asteroids);
                        if(isBulletInsideAsteroid(bullet, asteroid)){
                            oneDown = true;
                            if(asteroid->size != small) {
                                enqueue(asteroids, makeChildAsteroid(asteroid, randFloat(0.0, 2 * PI), randFloat(ASTEROID_MIN_VEL, ASTEROID_MAX_VEL)));
                                enqueue(asteroids, makeChildAsteroid(asteroid, randFloat(0.0, 2 * PI), randFloat(ASTEROID_MIN_VEL, ASTEROID_MAX_VEL)));
                            }
                            freeAsteroid(asteroid);
                            bullet->distCovered = bullet->range;
                        } else {
                            enqueue(asteroids, asteroid);
                        }
                    }
                    enqueue(bullets, bullet);
                }
            }
            
            if(ship->lives <= 0) {
                gameOver = true;
            }

            if(up && shipAlive) {
                animateShipFire(ship, screen);
            }
            if(shipAlive) {
                drawShip( ship, screen );
            } else {
                if( ((float) (clock() - lastDeath)) / CLOCKS_PER_SEC >= RESPAWN_DELAY_SECONDS ) {
                    bool shipCanSpawn = true;
                    for(int i = 0; i < queueSize(asteroids); i++) {
                        asteroid = (Asteroid *) dequeue(asteroids);
                        enqueue(asteroids, asteroid);
                        if( pointRoughlyNearAsteroid(ship->center, asteroid) ) {
                            shipCanSpawn = false;
                            break;
                        }
                        
                    }
                    shipAlive = shipCanSpawn;
                }
            }
            
            updateScreen(screen);
            lastUpdate = clock();
        }
	}
    SDL_Quit();
    freeShip( ship );
    
	return 0;
}