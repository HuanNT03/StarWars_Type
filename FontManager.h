#pragma once

#include "Game.h"
#include "string"

using std::string;

class FontManager
{
public:
	FontManager(const char* path, SDL_Renderer* ren ,int fontSize, Uint8 r, Uint8 b, Uint8 g);
	~FontManager();

	void loadRenderedText(const char* text);
	void update( int x, int y);
	void changeColor(Uint8 r, Uint8 b, Uint8 g);
	void render();

	const char* getContent() { return content.c_str(); }
	const char* at(int index);

	void changeRectColor(); // chua thuc hien duoc

	SDL_Rect getRect() { return desRect; }
	int getWidth() { return width; }
	int getHeight() { return height; }

private:

	string content;
	int xpos, ypos, width, height;
	int size;

	TTF_Font* font;
	SDL_Color textColor;
	SDL_Renderer* renderer;
	SDL_Texture* textTexture;
	SDL_Rect desRect;
	//SDL_Surface* textSurface;
	
};

