#pragma once

#include "Game.h"

class BackGround
{
public:
	BackGround(const char* path, SDL_Renderer* ren);
	~BackGround();

	void render();

private:
	SDL_Renderer* renderer;
	SDL_Texture* background;
	SDL_Rect destRect;
	int width, height;
};

