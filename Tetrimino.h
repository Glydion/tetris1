#ifndef TETRIMINO_H_INCLUDED
#define TETRIMINO_H_INCLUDED

#define CELL_WIDTH 18
#define CELL_HEIGHT 18
#define MOVE_DISTANCE 18

#include "SDL.h"
#include "SDL_image.h"

class Tetrimino
{
    public:
        Tetrimino(SDL_Renderer* renderer);
        ~Tetrimino();

        // 2D array of pieces and their shapes
        int figures[7][4] =
        {
            {1,3,5,7},        // I
            {2,4,5,7},        // Z
            {3,5,4,6},        // S
            {3,5,4,7},        // T
            {2,3,5,7},        // L
            {3,5,7,6},        // J
            {2,3,4,5},        // O
        };

        struct Point
        {int x, y;} a[4], b[4];

        void CreateShape();

        void Update(float delta);
        void Render(float delta);

        void HandleEvent(SDL_Event& e);

        void RotatePiece();
        void MovePiece();

    private:
        SDL_Texture* tileSet;
        SDL_Renderer* renderer;

        bool isMoving;
        bool isRotating;
        int moveDirection;
};

#endif // TETRIMINO_H_INCLUDED
