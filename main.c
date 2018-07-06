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

#define WIDTH 600
#define HEIGHT 600
#define DEPTH 32
#define SECONDS_BETWEEN_SHOTS .5
#define BULLET_SPEED 15.0
#define SHIP_SPEED 10.0

/**
    The program's starting point.

    @param argc number of command line arguments
    @param argv the command line arguments

    @return exit status of the program
*/
int main(int argc, char *argv[])
{
    SDL_Surface *screen;
    SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
   
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_RESIZABLE|SDL_HWSURFACE)))
    {
        SDL_Quit();
        return 1;
    }

    
    Ship *ship = createShip(200, 200, SHIP_SPEED);
    Color black = {.r = 0, .g = 0, .b = 0};
    Color white = {.r = 255, .g = 255, .b = 255};
    
    
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool gameOver = false;
    Bullet *bullet = NULL;
    Asteroid *asteroid = createAsteroid(200, 200, 0, 2.0, big);
    Queue *bullets = makeQueue();
    clock_t lastShot = clock();

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
                            down = true;
                            break;
                        case SDLK_ESCAPE:
                            gameOver = true;
                            break;
                        case SDLK_SPACE:
                            if( ((float) (clock() - lastShot)) / CLOCKS_PER_SEC >= SECONDS_BETWEEN_SHOTS ) {
                                Point tip = shipTip(ship);
                                bullet = createBullet(tip.x, tip.y, ship->direction, BULLET_SPEED, 300, 5, white);
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
                            down = false;
                            break;
                        default:
                            break;
                    }
                    break;
              }
         }
        
        if(up) {
            forwardObject((Object *) ship, screen);
        }
        else if(down) {
            reverseObject((Object *) ship, screen);
        }
        if(left) {
            rotateObject((Object *) ship, -.2);
        }
        else if(right) {
            rotateObject((Object *) ship, .2);
        }

        drawRect(screen, 0, 0, WIDTH, HEIGHT, black);
        
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

        /*
        if(bullet != NULL){
            moveBullet(bullet, screen);
            drawBullet(bullet, screen);
            if(hasCoveredDist(bullet)) {
                freeBullet(bullet);
                bullet = NULL;
            }
        }
        */
        forwardObject((Object *) asteroid, screen);
        drawAsteroid(asteroid, screen);
        drawShip( ship, screen );

        delayMs(20);
        updateScreen(screen);
	}
    SDL_Quit();
    freeShip( ship );
    
	return 0;
}