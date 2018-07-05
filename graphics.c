/**
    @file graphics.c
    @author Ben Fisher

    Defines functions dealing with graphics, such as drawing a line
    or a rectangle to a screen.
*/
#include "graphics.h"

void setpixel(SDL_Surface *screen, int x, int y, Color color ) {
    Uint32 *pixmem32;
    Uint32 colour;  
 
    colour = SDL_MapRGB( screen->format, color.r, color.g, color.b );
  
    pixmem32 = (Uint32*) screen->pixels  + y + x;
    *pixmem32 = colour;
}

void drawLine(SDL_Surface* screen, int x1, int y1, int x2, int y2, Color color) {

    if(SDL_MUSTLOCK(screen)) 
    {
        if(SDL_LockSurface(screen) < 0) return;
    }
    
    float dx = x2 - x1;
    float dy = y2 - y1;
    float x, y, step;
    int ytimesw;
    if(abs(dx) >= abs(dy)){
        step = abs(dx);
    } else {
        step = abs(dy);
    }

    dx /= step;
    dy /= step;
    
    x = x1;
    y = y1;
    for (int i = 1; i <= step; i++) {
        ytimesw = ((int) y)*screen->pitch/BPP;
        if(0 <= x && x < screen->w && 0 <= y && y < screen->h){
            setpixel(screen, (int) x, (int) ytimesw, color); 
        }
        x += dx;
        y += dy;
    }

    
}

void drawRect(SDL_Surface* screen, int x, int y, int width, int height, Color color) {
    #include <stdio.h>
    int ytimesw;
  
    if(SDL_MUSTLOCK(screen)) 
    {
        if(SDL_LockSurface(screen) < 0) return;
    }
    int lastX = x + width;
    int lastY = y + height;
    int startX = x;
    int startY = y;
    for(int x = startX; x < lastX; x++) {
        for(int y = startY; y < lastY; y++) {
            ytimesw = y*screen->pitch/BPP;
            if(0 <= x && x < screen->w && 0 <= y && y < screen->h){
                setpixel(screen, x, ytimesw, color); 
            }
            //printf("%d %d\n", x, ytimesw);
        }
    }

}

void updateScreen(SDL_Surface* screen) {
    if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  
    SDL_Flip(screen); 
}