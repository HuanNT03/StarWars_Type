#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* path, SDL_Renderer* ren, int x, int y, int w, int h);
	~GameObject();

	void update(int x, int y);
	void render();
	SDL_Rect getRect() { return destRect; }
private:

	int xpos;
	int ypos;
	float ratio;
	int textureWidth, textureHeight;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};

