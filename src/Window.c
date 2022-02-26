#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Window.h"
#include "Player.h"
#include "Enviorment.h"
#include "Gun.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int sinceLastTextUpdate = 0;
int textUpdateRate = 200;
int sinceLastTimeUpdate = 0;

SDL_Surface* timeSurface;
SDL_Texture* timeTex;
SDL_Rect timeRect;

int startTime = 0;

SDL_Color yellow = {255, 255, 0};

char temp0[64];
TTF_Font* pixelFont;

void InitWindow(){
    window = SDL_CreateWindow("1v1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 786, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    sinceLastTextUpdate = SDL_GetTicks();

    timeRect.x = 0;
    timeRect.y = 0;
    timeRect.w = 500;
    timeRect.h = 100;

        pixelFont = TTF_OpenFont("Pixelmania.ttf", 25);

    timeSurface = TTF_RenderText_Solid(font, "TIME", yellow);
    sinceLastTimeUpdate = SDL_GetTicks();


    timeTex = SDL_CreateTextureFromSurface(renderer, timeSurface);

}
void Render(){

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRects(renderer, enviorment, amountOfObjects);
    SDL_RenderFillRects(renderer, bullets, amountOfBullets);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect[0]);
    SDL_RenderDrawLine(renderer, laserPos[0], laserPos[1], laserPos[2], laserPos[3]);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect[1]);
    SDL_RenderDrawLine(renderer, laserPos[4], laserPos[5], laserPos[6], laserPos[7]);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    if(SDL_GetTicks() - textUpdateRate >= sinceLastTextUpdate){
        if(hasWon){
            
            winTex = SDL_CreateTextureFromSurface(renderer, winSurface);
            SDL_RenderCopy(renderer, winTex, NULL, &winRect);
        }
        SDL_DestroyTexture(scoreTex);
        scoreTex = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    }
    TimeDisplay();

    if(!hasWon){
        SDL_RenderCopy(renderer, scoreTex, NULL, &scoreRect);
        SDL_RenderCopy(renderer, timeTex, NULL, &timeRect); 
    }
 

    SDL_RenderPresent(renderer);
}

void TimeDisplay(){
    if(SDL_GetTicks() - sinceLastTimeUpdate >= 200){
        sinceLastTimeUpdate = SDL_GetTicks();
        sprintf(temp0, "%f", floor((SDL_GetTicks() - startTime) / 1000));
        SDL_FreeSurface(timeSurface);
        timeSurface = TTF_RenderText_Solid(pixelFont, temp0, yellow);
        SDL_DestroyTexture(timeTex);

        timeTex = SDL_CreateTextureFromSurface(renderer, timeSurface);
    }
}