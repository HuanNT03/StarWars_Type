#pragma once

#include<iostream>
#include<time.h>
#include<cstdlib>
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
#include"SDL_ttf.h"


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	//SDL_Renderer* ren;

private:
	int count;
	int currentButton;
	bool isRunning;
	bool isPlaying;
	bool inStartScreen;
	bool GameOver;

	SDL_Window* window;
	SDL_Renderer* renderer;
};

