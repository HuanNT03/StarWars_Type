#include "TextureManager.h"


SDL_Texture* TextureManager::loadTexture(const char* path, SDL_Renderer* ren)
{
	SDL_Surface* tempSurface = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);

	SDL_FreeSurface(tempSurface);

	return tex;
}