#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* path, SDL_Renderer* ren, int x, int y, int w, int h)
{
	renderer = ren;
	ratio = float(w) / h;
	objTexture = TextureManager::loadTexture(path, ren);
	SDL_QueryTexture(objTexture, NULL, NULL, &textureWidth, &textureHeight);
	xpos = x;
	ypos = y;
	if (ratio == (float(textureWidth) / textureHeight))
	{
		destRect = { x, y, w, h };
	}
	else if (ratio > (float(textureWidth) / textureHeight)) //Rect wider image
	{
		destRect.w = textureWidth * h / textureHeight;
		destRect.x =  x + (w - destRect.w) / 2;
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

GameObject::~GameObject()
{
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (objTexture != NULL)
	{
		SDL_DestroyTexture(objTexture);
		objTexture = NULL;
	}
}

void GameObject::update(int x, int y)
{
	xpos = x;
	ypos = y;
	destRect.x = x;
	destRect.y = y;
}

void GameObject::render()
{
	SDL_RenderCopy(renderer, objTexture, NULL/*&srcRect*/, &destRect);
}