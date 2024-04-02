#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include"useForAll.h"

using namespace std;

#ifndef CLASS_H
#define CLASS_H


TTF_Font* gFont;
SDL_Texture* value[11]; // cac so 2 4 8 .. trong bang 
bool isChange = 1;

class lBlock
{
    private:
        SDL_Texture* currentTexture;

    public:
        int val;
        int i, j, ni, nj, x, y;

        lBlock()
        {
            currentTexture = NULL;
            val = 0;
            i = j = ni = nj = x = y = -1;
        }


        ~lBlock()
        {
            free();
        }


        void free()
        {
            if(currentTexture != NULL) 
            {
                SDL_DestroyTexture(currentTexture);
                currentTexture = NULL;
            }
            val = 0;
        }

        void render(int x, int y, SDL_Rect* clip = NULL)
        {
            SDL_Rect pos = {x, y, BLOCK_EDGE, BLOCK_EDGE};
            if(clip != NULL)
            {
                pos.w = clip->w;
                pos.h = clip->h;
            }
            SDL_RenderCopy(gRenderer, currentTexture, clip, &pos);
        }

        void update()
        {
            currentTexture = value[val];
        }

        bool notInRightPlace()
        {
            return (i != ni || j != nj);
        }

}block0;

lBlock block[4][4];
/*
    - v[0] chứa các ô có giá trị > 0 
    - ví dụ v[0] chứa x, y, z thì khi di chuyển y sẽ được cộng vào x
    => ở hàm shortenVector thì ni nj của ô x sẽ lưu i j của ô y
        để khi update sẽ có vị trí của ô y.
        Lúc này ni nj sẽ mang ý nghĩa là vị trí mới của ô y
*/
void shortenVector(vector<lBlock>v[2])
{
    for(int j = 0; j < int(v[0].size()); j++) 
    {
        if(j < int(v[0].size())-1 && 
            v[0][j].val == v[0][j+1].val)
        {
            v[0][j].val++;
            score += (1LL << v[0][j].val);

            // luu lại vị trí của ô (j+1)
            v[0][j].ni = v[0][j+1].i;
            v[0][j].nj = v[0][j+1].j;

            v[1].push_back(v[0][j]);
            j++;
        }
        else v[1].push_back(v[0][j]);
    }
}

void copyBlock(lBlock &tmp, lBlock &origin)
{
    tmp.val = origin.val;
    tmp.i = origin.i;
    tmp.j = origin.j;
}

// z chay trong v[1]
void updateBlock(int &i, int &j, int &z, vector<lBlock>v[2])
{
    block[i][j].val = 0;
    if(z < int(v[1].size()))
    {
        // cap nhat vi tri moi cho o (i, j)
        block[ v[1][z].i ][ v[1][z].j ].ni = i;
        block[ v[1][z].i ][ v[1][z].j ].nj = j;

        /*
        neu o (i, j) duoc cong tu mot o khac, thi 
        ni nj dang luu vi tri cua o do
        => cap nhat vi tri cho o do
        */
        if(v[1][z].ni != -1)
        {
            block[ v[1][z].ni ][ v[1][z].nj ].ni = i;
            block[ v[1][z].ni ][ v[1][z].nj ].nj = j;
            isChange = 1;
        }
        block[i][j].val = v[1][z].val;

        if(block[ v[1][z].i ][ v[1][z].j ].notInRightPlace())
            isChange = 1;
    }
}


void moveDown()
{
    for(int i = 0; i < 4; i++) // for cot
    {
        vector<lBlock>v[2];
        // lay ra nhung phan tu co gia tri > 0
        for(int j = 3; j >= 0; j--)
        {
            lBlock tmp;
            copyBlock(tmp, block[i][j]);
            if(block[i][j].val > 0) v[0].push_back(tmp);
        }

        shortenVector(v);
        for(int j = 3, z = 0; j >= 0; j--, z++)
        {
            updateBlock(i, j, z, v);
        }
    }
}

void moveUp()
{
    for(int i = 0; i < 4; i++)
    {
        vector<lBlock>v[2];
        for(int j = 0; j < 4; j++)
        {
            lBlock tmp;
            copyBlock(tmp, block[i][j]);
            if(block[i][j].val > 0) v[0].push_back(tmp);
        }

        shortenVector(v);
        for(int j = 0, z = 0; j < 4; j++, z++)
        {
            updateBlock(i, j, z, v);
        }
    }
}

void moveLeft()
{
    for(int j = 0; j < 4; j++)
    {
        vector<lBlock>v[2];
        for(int i = 0; i < 4; i++)
        {
            lBlock tmp;
            copyBlock(tmp, block[i][j]);
            if(block[i][j].val > 0) v[0].push_back(tmp);
        }

        shortenVector(v);
        for(int i = 0, z = 0; i < 4; i++, z++)
        {
            updateBlock(i, j, z, v);
        }
    }
}

void moveRight()
{
    for(int j = 0; j < 4; j++)
    {
        vector<lBlock>v[2];
        for(int i = 3; i >= 0; i--)
        {
            lBlock tmp;
            copyBlock(tmp, block[i][j]);
            if(block[i][j].val > 0) v[0].push_back(tmp);
        }

        shortenVector(v);
        for(int i = 3, z = 0; i >= 0; i--, z++)
        {
            updateBlock(i, j, z, v);
        }
    }
}

void generate()
{
    if(!isChange) return;
    
    int cnt = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++) cnt += (block[i][j].val == 0);
    }

    int pos = rand()%cnt + 1;
    cnt = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(block[i][j].val == 0)
            {
                cnt++;
                if(cnt == pos)
                {
                    block[i][j].val = 1;
                    score += 2;
                    return;
                }
            }
        }
    }
}

void blockMovement(SDL_Event &e)
{
    if(moving) return;
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 &&
        (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP ||
         e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT
        )
      )
    {
        isChange = 0;
        moving = 1;
        switch(e.key.keysym.sym)
        {
            case SDLK_DOWN:
                BLOCK_VY += BLOCK_V;
                moveDown();
                break;
            case SDLK_UP:
                BLOCK_VY -= BLOCK_V;
                moveUp();
                break;
            case SDLK_LEFT:
                BLOCK_VX -= BLOCK_V;
                moveLeft();
                break;
            case SDLK_RIGHT:
                BLOCK_VX += BLOCK_V;
                moveRight();
                break;
        }

        generate();
        best = max(best, score);
    }
}

#endif