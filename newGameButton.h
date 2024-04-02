#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"useForAll.h"
using namespace std;

#ifndef NEWGAMEBUTTON_H
#define NEWGAMEBUTTON_H

class newGameButton
{
    private: 
        SDL_Texture* texture[2];
        bool inside, buttonDown;
        int x, y, w, h;
    
    public:
        newGameButton()
        {
            x = y = w = h = 0;
            texture[0] = texture[1] = NULL;
        }

        void imgLoad()
        {
            SDL_Surface *tmpSurface = NULL;

            tmpSurface = IMG_Load("images/new.png");
            texture[0] = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

            tmpSurface = IMG_Load("images/newDown.png");
            texture[1] = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

            SDL_FreeSurface(tmpSurface);
        }

        void render(int i)
        {
            SDL_Rect rect = {x, y, w, h};
            SDL_RenderCopy(gRenderer, texture[i], NULL, &rect);
        }

        void updatePos(SDL_Rect &rect)
        {
            x = rect.x;
            y = rect.y;
            w = rect.w;
            h = rect.h;
        }

        void event(SDL_Event &e)
        {
            if(e.type == SDL_MOUSEMOTION || 
                e.type == SDL_MOUSEBUTTONDOWN ||
                e.type == SDL_MOUSEBUTTONUP )
            {
                int cx, cy;
                SDL_GetMouseState(&cx, &cy);

                inside = 1;
                buttonDown = 0;
                if(cx < x || cx > x+w || cy < y || cy > y+h) inside = 0;
                else
                {
                    if(e.type == SDL_MOUSEBUTTONDOWN) buttonDown = 1;
                    if(e.type == SDL_MOUSEBUTTONUP) 
                    {
                        buttonDown = 0;
                        restart = 1;
                    }
                }
            }
        }

        void drawButton()
        {
            if(buttonDown == 0) render(0);
            else render(1);
        }
}newButton;

#endif