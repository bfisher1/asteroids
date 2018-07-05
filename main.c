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
#include <SDL/SDL.h>
#include "util.h"
#define WIDTH 600
#define HEIGHT 600
#define DEPTH 32

/**
    The program's starting point.
*/
int main()
{
    SDL_Surface *screen;
    SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
   
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_RESIZABLE|SDL_HWSURFACE)))
    {
        SDL_Quit();
        return 1;
    }

    Point *points = malloc( sizeof(Point) * 4 );
    points[0].x = 40;
    points[0].y = 40;
    points[1].x = 40;
    points[1].y = -40;
    points[2].x = -40;
    points[2].y = 40;
    points[3].x = -40;
    points[3].y = -40;
    
    Object *object = (Object *) malloc(sizeof(Object));
    Color white = {.r = 255, .g = 255, .b = 255};
    Color black = {.r = 0, .g = 0, .b = 0};
    fillObject( object, 200, 200, points, 4, 10.0, 0, white );
    
    drawObject( object, screen );
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool gameOver = false;

	while(!gameOver) {
        drawRect(screen, 0, 0, WIDTH, HEIGHT, black);
        drawObject( object, screen );
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
                        case SDLK_SPACE:
                            gameOver = true;
                            break;
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
                        case SDLK_SPACE:
                            gameOver = false;
                            break;
                        default:
                            break;
                    }
                    break;
              }
         }
        
        if(up) {
            forwardObject(object);
        }
        else if(down) {
            reverseObject(object);
        }
        if(left) {
            rotateObject(object, -.2);
        }
        else if(right) {
            rotateObject(object, .2);
        }
        delayMs(20);
         updateScreen(screen);
	}
    freeObject( object );
    SDL_Quit();
	return 0;
}