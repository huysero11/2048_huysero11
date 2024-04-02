#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"useForAll.h"
#include"class.h"
#include"newGameButton.h"
#include"score.h"

using namespace std;

#ifndef BOARD_H
#define BOARD_H

SDL_Point pos[4][4];

void setUpBoard()
{
    int x = GAP + GAP;
    for(int i = 0; i < 4; i++)
    {
        int y = GAP + BUTTON_HEIGHT + GAP + GAP;
        for(int j = 0; j < 4; j++)
        {
            block[i][j].i = block[i][j].ni = i;
            block[i][j].j = block[i][j].nj = j;

            block[i][j].x = x;
            block[i][j].y = y;

            pos[i][j] = {x, y};

            y += GAP + BLOCK_EDGE;
        }
        x += GAP + BLOCK_EDGE;
    }


    SDL_Rect rect = {GAP, GAP,
                    (WINDOW_WIDTH - GAP*4)/3, BUTTON_HEIGHT};
    newButton.updatePos(rect);

    rect = {WINDOW_WIDTH - GAP - (WINDOW_WIDTH - GAP*4)/3, GAP,
            (WINDOW_WIDTH - GAP*4)/3, BUTTON_HEIGHT};
    SDL_RenderFillRect(gRenderer, &rect);
    lScore.updatePos(rect);

    rect = {GAP*2 + (WINDOW_WIDTH - GAP*4)/3, GAP,
            (WINDOW_WIDTH - GAP*4)/3, BUTTON_HEIGHT};
    SDL_RenderFillRect(gRenderer, &rect);
    lBest.updatePos(rect);
}

void makeNewGame()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++) block[i][j].val = 0;
    }
    lose = 0;
    restart = 0;
    score = 0;
    generate();
}

void drawBoard()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_Rect rect = {GAP, GAP + BUTTON_HEIGHT + GAP,
                    BOARD_EDGE, BOARD_EDGE};
    SDL_RenderFillRect(gRenderer, &rect);

    newButton.drawButton();

    lBest.render();
    lBest.textLoad(best);
    lBest.renderText();

    lScore.render();
    lScore.textLoad(score);
    lScore.renderText();


    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            block0.render(pos[i][j].x, pos[i][j].y);
        }
    }
}


bool movingBlock()
{
    bool stillMove = 0;

    /*
    - Nếu vuốt sang trái hoặc lên trên, thì sẽ phải render ô ở trái và ở trên trước
    => for i j xuôi từ 0 đến 3
    - Nếu vuốt sang phải hoặc xuống dưới, thì sẽ phải render ô ở bên phải và ở dưới trước
    => for i j ngược từ 3 về 0
    */

    if(BLOCK_VX < 0 || BLOCK_VY < 0)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(block[i][j].notInRightPlace())
                {
                    stillMove = 1;
                    if(block[i][j].x != pos[ block[i][j].ni ][ block[i][j].nj ].x)
                    {
                        block[i][j].x += BLOCK_VX * abs(block[i][j].ni - i);
                    }
                    else block[i][j].ni = i;

                    if(block[i][j].y != pos[ block[i][j].ni ][ block[i][j].nj ].y)
                    {
                        block[i][j].y += BLOCK_VY * abs(block[i][j].nj - j);
                    }
                    else block[i][j].nj = j;
                }

                block[i][j].render(block[i][j].x, block[i][j].y);
            }
        }
    } 

    else
    {
        for(int i = 3; i >= 0; i--)
        {
            for(int j = 3; j >= 0; j--)
            {
                if(block[i][j].notInRightPlace())
                {
                    stillMove = 1;
                    if(block[i][j].x != pos[ block[i][j].ni ][ block[i][j].nj ].x)
                    {
                        block[i][j].x += BLOCK_VX * abs(block[i][j].ni - i);
                    }
                    else block[i][j].ni = i;

                    if(block[i][j].y != pos[ block[i][j].ni ][ block[i][j].nj ].y)
                    {
                        block[i][j].y += BLOCK_VY * abs(block[i][j].nj - j);
                    }
                    else block[i][j].nj = j;
                }

                block[i][j].render(block[i][j].x, block[i][j].y);
            }
        }
    }


    if(!stillMove) 
    {
        BLOCK_VX = 0;
        BLOCK_VY = 0;
    }
    return stillMove;
}


void updateBoard()
{
    if(moving) moving = movingBlock();
    else
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                block[i][j].x = pos[i][j].x;
                block[i][j].y = pos[i][j].y;
                block[i][j].update();
                block[i][j].render(pos[i][j].x, pos[i][j].y);
            }
        }
    }
}


#endif