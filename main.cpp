#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include"class.h"
#include"board.h"
#include"useForAll.h"
#include"loseAndWin.h"
#include"newGameButton.h"
#include"score.h"

using namespace std; 


void start()
{
    setUpBoard();

    block0.val = 0;
    block0.update();

    generate();
    drawBoard();
    updateBoard();

    SDL_Event e;
    bool quit = 0;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) 
            {
                quit = 1;
                lBest.save();
            }
            checkLose();
            blockMovement(e);
            newButton.event(e);
        }

        if(restart) makeNewGame();
        drawBoard();
        updateBoard();

        if(!lose) SDL_RenderPresent(gRenderer);
        else printLoseScreen(); 
    }
}


void init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)) cout << "fail";
    gWindow = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}


void close()
{
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}


void loadMedia()
{
    SDL_Surface* tmpSurface = NULL;
    for(int i = 0; i <= 10; i++)
    {
        stringstream s("");
        s << "images/" << (1 << i) << ".png";
        tmpSurface = IMG_Load(s.str().c_str());

        value[i] = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    }

    tmpSurface = IMG_Load("images/background.png");
    background = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

    SDL_FreeSurface(tmpSurface);


    loadLoseAndWinScreen();
    newButton.imgLoad();
    lBest.imgLoad("images/best.png");
    lScore.imgLoad("images/score.png");


    font = TTF_OpenFont("images/font1.ttf", 35);

    ifstream getBestScore("images/scoreSave.txt");
    getBestScore >> best;
    getBestScore.close();
}


int main(int argv, char* argc[])
{
    srand(time(0));
    init();
    loadMedia();

    start();
    close();

    return 0;
}