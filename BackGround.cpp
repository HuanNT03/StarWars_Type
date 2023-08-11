#include"BackGround.h"
#include "TextureManager.h"

using std::cout;
using std::endl;

BackGround::BackGround(const char* path, SDL_Renderer* ren)
{
	renderer = ren;
	background = TextureManager::loadTexture(path, ren);
	if (background == NULL)
	{
		cout << "Failed to load background! SDL error: " << SDL_GetError() << endl;
	}
}

BackGround::~BackGround()
{
	if (background != NULL)
	{
		SDL_DestroyTexture(background);
		background = NULL;
	}
}

void BackGround::render()
{
	SDL_RenderCopy(renderer, background, NULL, NULL);
}