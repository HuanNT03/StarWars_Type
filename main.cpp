#include<iostream>
#include"SDL.h"
#include"Game.h"
#include"config.h"

Uint32 frameStart;

int frameTime;

Game* game = nullptr;

int main(int argc, char* args[]) 
{
	game = new Game();
	game->init(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while(game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}