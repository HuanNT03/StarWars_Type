#pragma once

#include "Game.h"
#include "BasicFunc.h"
#include <math.h>

class Laser
{
public:
	Laser(const char* path, SDL_Renderer* ren, int x, int y, int w, int h);
	~Laser();
	void update(int xdes, int ydes);
	void render();
	void moveToPoint(int& xStart, int& yStart, int xDest, int yDest, int velocity);
	SDL_Rect getRect() { return destRect; }
	bool reachDest() { return arrive; }

private:
	double angle;
	float ratio;
	int textureWidth;
	int textureHeight;
	bool arrive = false;

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect destRect;
};

