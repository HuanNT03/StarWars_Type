#include "FontManager.h"

using std::cout;
using std::endl;

FontManager::FontManager(const char* path, SDL_Renderer* ren, int fontSize, Uint8 r, Uint8 b, Uint8 g)
{
	size = fontSize;
	renderer = ren;
	textColor = { r, b, g };
	font = TTF_OpenFont(path, fontSize);
	if (font == NULL)
	{
		cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
	}

}

FontManager::~FontManager()
{
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}
	
	if (textTexture != NULL)
	{
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
	}
}


void FontManager::loadRenderedText(const char* text)
{
	content = text;
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);

	if (textSurface == NULL)
	{
		cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
	}
	else
	{
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (textTexture == NULL)
		{
			cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
}

void FontManager::changeColor(Uint8 r, Uint8 b, Uint8 g)
{
	textColor = { r, b, g };
	loadRenderedText(content.c_str());

}

void FontManager::update(int x, int y)
{
	xpos = x;
	ypos = y;

	desRect.x = xpos;
	desRect.y = ypos;
	desRect.w = width;
	desRect.h = height;
	
}

void FontManager::render()
{
	SDL_RenderCopy(renderer, textTexture, NULL, &desRect);
}

void FontManager::changeRectColor()
{
	//SDL_FillRect(textSurface, &desRect, SDL_MapRGB( textSurface->format, 255, 0, 255));
}

const char* FontManager::at(int index)
{
	char at = content[index];
	const char* letterAt = &at;
	//cout << "contentAt:" << *(letterAt) << endl;
	return letterAt;
}

