#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"useForAll.h"

#ifndef LOSEANDWIN_H
#define LOSEANDWIN_H


using namespace std;

SDL_Texture* winScreen = NULL;
SDL_Texture* loseScreen = NULL;
SDL_Rect rectLoseWin = {WINDOW_WIDTH/4, WINDOW_HEIGHT/4,
                        WINDOW_WIDTH/2, WINDOW_HEIGHT/2};


void loadLoseAndWinScreen()
{
    SDL_Surface* tmpSurface = NULL;

    tmpSurface = IMG_Load("images/win.png");
    winScreen = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

    tmpSurface = IMG_Load("images/lose.png");
    loseScreen = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
}

void printWinScreen()
{
    SDL_RenderCopy(gRenderer, winScreen, NULL, &rectLoseWin);
    SDL_RenderPresent(gRenderer);
}

void printLoseScreen()
{
    SDL_RenderCopy(gRenderer, loseScreen, NULL, &rectLoseWin);
    SDL_RenderPresent(gRenderer);
}


void checkLose()
{
    int cnt = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++) cnt += (block[i][j].val == 0);
    }

    if(cnt == 0)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(i < 3 && block[i][j].val == block[i+1][j].val) return;
                if(j < 3 && block[i][j].val == block[i][j+1].val) return;
            }
        }
        lose = 1;
        return;
    }
    return;
}

#endif