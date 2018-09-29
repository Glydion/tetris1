#include "Game.h"

Game::Game()
{
    window = 0;
    renderer = 0;
}

Game::~Game()
{

}

bool Game::Init()
{
    // Initialize the SDL video and audio subsystems
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Create window
    window = SDL_CreateWindow("Tetris v1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

    if(!window)
    {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    // Enable TTF loading
    TTF_Init();

    // Load the fonts
    fontScore = TTF_OpenFont("Munro.ttf", 20);

    // Initialize SDL mixer
    if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
    {
        std::cout << "Error initializing SDL mixer: " << Mix_GetError() << std::endl;
        return false;
    }

    // Load music
    gameMusic = Mix_LoadMUS("sounds/tetris.mp3");
    if( !gameMusic )
    {
        std::cout << "Error loading Tetris music: " << Mix_GetError() << std::endl;
        return false;
    }

    // Load sounds

    // Seed random number generation
    srand(time(0));

    // Initialize timing
    lastTick = SDL_GetTicks();
    fpsTick = lastTick;
    fps = 0;                    // Set starting FPS value
    frameCount = 0;             // Set starting frame count

    return true;
}

void Game::Clean()
{
    // Clean resources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_FreeMusic(gameMusic);
    gameMusic = NULL;

    // Clean test data
    SDL_DestroyTexture(sTexture);
}

void Game::Run()
{
    // Create game objects
    testPiece = new Tetrimino(renderer);

    // Start the game music
    Mix_PlayMusic(gameMusic,-1);

    // Start a new game
    NewGame();

    // Main game loop
    while(1)
    {
        // Event handler
        SDL_Event e;

        // If event is a QUIT event, stop the program
        if(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                break;
            }

            // Handle input for the Tetrimino
            testPiece->HandleEvent(e);
        }

        // Calculate delta and fps
        unsigned int curTick = SDL_GetTicks();
        float delta = (curTick - lastTick) / 1000.0f;

        // Cap FPS delay to specific amount
        if(curTick - fpsTick > FPS_DELAY)
        {
            fps = frameCount * (1000.0f / (curTick - fpsTick));
            fpsTick = curTick;
            frameCount = 0;
            //std::cout << "FPS: " << fps << std::endl;
            char buf[100];
            snprintf(buf,100,"Tetris v1.0 (fps: %u)",fps);
            SDL_SetWindowTitle(window,buf);
        }
        else
        {
            frameCount++;
        }

        lastTick = curTick;

        // Update and render the game
        Update(delta);
        Render(delta);
    }

    delete testPiece;

    Clean();

    // Close the fonts
    TTF_CloseFont(fontScore);

    // Close all subsystems
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Game::NewGame()
{

}

void Game::Update(float delta)
{
    // Update the Tetrimino test piece
    testPiece->Update(delta);
}

void Game::Render(float delta)
{
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Render the game objects
    testPiece->Render(delta);

    // Present the renderer to display
    SDL_RenderPresent(renderer);
}
