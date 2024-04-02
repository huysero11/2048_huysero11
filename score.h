#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"useForAll.h"

using namespace std;

#ifndef SCORE_H 
#define SCORE_H 

class lTexture
{
    private:
        SDL_Texture *texture;
        SDL_Texture *textTexture;
        SDL_Rect rect;
        int x, y, w, h;
    
    public:
        lTexture()
        {
            texture = NULL;
            textTexture = NULL;
            x = y = 0;
        }


        void imgLoad(string s)
        {
            SDL_Surface *tmpSurface = NULL;
            tmpSurface = IMG_Load(s.c_str());
            texture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);
        }


        void textLoad(int number)
        {
            SDL_Surface *tmpSurface = NULL;
            stringstream ss("");
            ss << number;

            SDL_Color color = {0, 0, 0};
            tmpSurface = TTF_RenderText_Blended(font, ss.str().c_str(), color);
            textTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

            w = tmpSurface->w;
            h = tmpSurface->h;

            SDL_FreeSurface(tmpSurface);
        }

        void updatePos(SDL_Rect &nRect)
        {
            rect = nRect;
        }


        void render()
        {
            SDL_RenderCopy(gRenderer, texture, NULL, &rect);
        }

        void renderText()
        {
            SDL_Rect pos = {rect.x + (rect.w - w)/2,
                            rect.y + 4*(rect.h - h)/5,
                            w, h};
            SDL_RenderCopy(gRenderer, textTexture, NULL, &pos);
        }

        void save()
        {
            ofstream saveBestScore("images/scoreSave.txt");
            saveBestScore << best;
            saveBestScore.close();
        }
};

lTexture lScore;
lTexture lBest;

#endif