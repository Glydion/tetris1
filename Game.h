#ifndef GAME_H_
#define GAME_H_

// Preprocessors
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cmath>
#include <vector>

// Inclusions for game objects
#include "Tetrimino.h"

// Macros
#define FPS_DELAY       500
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   480
#define GRID_WIDTH      10
#define GRID_HEIGHT     20


class Game
{
    public:
        Game();
        ~Game();

        bool Init();
        void Run();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        // Game objects
        Tetrimino* testPiece;

        // Audio objects
        Mix_Music* gameMusic = NULL;

        // Timing
        unsigned int lastTick, fpsTick, fps, frameCount;

        // Font objects
        TTF_Font* fontScore;
        std::stringstream sValue;
        SDL_Texture* sTexture;
        int sWidth, sHeight;

        // Standard game functions
        void Clean();
        void Update(float delta);
        void Render(float delta);
        void NewGame();


};

#endif // GAME_H_
