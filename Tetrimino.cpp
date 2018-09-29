#include "Tetrimino.h"

Tetrimino::Tetrimino(SDL_Renderer* renderer)
{
    // Initialize data members
    this->renderer = renderer;

    // Initialize tile set spritesheet
    SDL_Surface* surface = IMG_Load("images/tiles.png");
    tileSet = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    CreateShape();
}

Tetrimino::~Tetrimino()
{

}

void Tetrimino::CreateShape()
{
    int n = 3;

    //if(a[0].x == 0)
    //{
        for( int i = 0; i < 4; i++ )
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
        }
    //}
}

void Tetrimino::RotatePiece()
{
    if(isRotating)
    {
        // Determine the center of rotation
        Point p = a[1];

        for(int i = 0; i < 4; i++)
        {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
    }
}

void Tetrimino::MovePiece()
{
    if(isMoving)
    {
        switch(moveDirection)
        {
            case -1:
            {
                for(int i = 0; i < 4; i++)
                {
                    a[i].x -= moveDirection;
                }
                break;
            }

            case 1:
            {
                for(int i = 0; i < 4; i++)
                {
                    a[i].x += moveDirection;
                }
                break;
            }

            case 2:
            {
                for(int i = 0; i < 4; i++)
                {
                    a[i].y += 1;
                }
            }
        }
    }
}

void Tetrimino::HandleEvent(SDL_Event& e)
{
    // If a key was pressed...
    if(e.type == SDL_KEYDOWN)
    {
        // Check which key was pressed
        switch(e.key.keysym.sym)
        {
            case SDLK_LEFT:
            {
                isMoving = true;
                moveDirection = -1;
                break;
            }

            case SDLK_RIGHT:
            {
                isMoving = true;
                moveDirection = 1;
                break;
            }

            case SDLK_DOWN:
            {
                isMoving = true;
                moveDirection = 2;
                break;
            }

            case SDLK_SPACE:
            {
                isRotating = true;
                break;
            }
        }
    }

    // If a key was released...
    else if(e.type == SDL_KEYUP)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_LEFT:
            {
                // Stop moving the Tetrimino left
                isMoving = false;
                moveDirection = 0;
                break;
            }

            case SDLK_RIGHT:
            {
                // Stop moving the Tetrimino right
                isMoving = false;
                moveDirection = 0;
                break;
            }

            case SDLK_DOWN:
            {
                isMoving = false;
                moveDirection = 0;
                break;
            }

            case SDLK_SPACE:
            {
                // Stop rotating the Tetrimino
                isRotating = false;
                break;
            }
        }
    }
}

void Tetrimino::Update(float delta)
{
    // Every frame, check to see whether
    // to move or rotate the Tetrimino (or both)
    this->RotatePiece();
    this->MovePiece();
}

void Tetrimino::Render(float delta)
{
    // Render all tiles of the tetrimino piece
    for( int i = 0; i < 4; i++ )
    {
        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = CELL_WIDTH;
        srcRect.h = CELL_HEIGHT;

        // Set destination rectangle for each tile
        SDL_Rect dstRect;
        dstRect.x = a[i].x * CELL_WIDTH;
        dstRect.y = a[i].y * CELL_HEIGHT;
        dstRect.w = CELL_WIDTH;
        dstRect.h = CELL_HEIGHT;

        SDL_RenderCopy(renderer,tileSet,&srcRect,&dstRect);
    }
}
