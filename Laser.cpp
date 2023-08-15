#include "Laser.h"
#include "TextureManager.h"

Laser::Laser(const char* path, SDL_Renderer* ren, int x, int y, int w, int h)
{
	renderer = ren;
	renderer = ren;
	ratio = float(w) / h;
	texture = TextureManager::loadTexture(path, ren);
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	if (ratio == (float(textureWidth) / textureHeight))
	{
		destRect = { x, y, w, h };
	}
	else if (ratio > (float(textureWidth) / textureHeight)) //Rect wider image
	{
		destRect.w = textureWidth * h / textureHeight;
		destRect.x = x + (w - destRect.w) / 2;
		destRect.y = y;
		destRect.h = h;
	}
	else //Rect taller than image
	{
		destRect.h = textureHeight * w / textureWidth;
		destRect.y = y + (h - destRect.h) / 2;
		destRect.x = x;
		destRect.w = w;
	}
}

Laser::~Laser()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void Laser::update(int xdes, int ydes)
{
	moveToPoint(destRect.x, destRect.y, xdes, xdes, 20);
}

void Laser::render()
{
	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
}

void Laser::moveToPoint(int& xStart, int& yStart, int xDest, int yDest, int velocity)
{
	yStart -= velocity;
}