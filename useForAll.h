#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#ifndef USEFORALL_H
#define USEFORALL_H

const int WINDOW_HEIGHT = 690;
const int WINDOW_WIDTH = 590;

const int BOARD_EDGE = 570;
const int BUTTON_HEIGHT = 90;
const int BLOCK_EDGE = 130;

const int GAP = 10; // khoang cach giua cac block

const int BLOCK_V = 20; // van toc chuyen dong
int BLOCK_VX = 0;
int BLOCK_VY = 0;

int point = 0;
bool lose = 0;
bool win = 0;
bool moving = 0;
bool restart = 0;

long long score = 0;
long long best = 0;

TTF_Font* font = NULL;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *background = NULL;

// cur = currentTexture
// generate() = nextStep()

#endif 