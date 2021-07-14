//Using SDL and standard IO
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <memory>
//#include <functional>
#include <string>
#include <vector>
#include <iostream>

#include "kiss_sdl/kiss_sdl.h"

#include "intro.h"
#include "menu.h"
#include "highscore.h"
#include "singleplayer.h"

int main( int argc, char* args[] )
{
	GameEngine game;

	bool quit = false;

	std::cout << "Game starts" << "\n";

	if( !game.Init() ){
		printf( "Failed to initialize!\n" );
	}
	else
	{
		while ( game.Running() )
		{
			game.HandleEvents();
			game.Draw();
			game.Update();
		}
	}

	//Free resources and close SDL
	game.Cleanup();

	return 0;
}
