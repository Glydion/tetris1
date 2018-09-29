//******************************************
// Tetris - v1.0.0
// By: Pedro Miranda Jr. (Glydion)
//
// Start Date: Sunday July 8, 2018
// Finish Date:
//******************************************

#include "main.h"

int main( int argc, char* argv[] )
{
    // Create the game object
    Game* game = new Game();

    // Initialize and run the game
    if( game->Init() )
    {
        game->Run();
    }

    // Clean up
    delete game;

    return 0;
}
