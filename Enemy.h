#pragma once

#include "Game.h"
#include "GameObject.h"
#include "FontManager.h"

class Enemy
{
public:
	Enemy(SDL_Renderer* ren, const char* text);
	~Enemy();

	void update();
	void render();
	void moveToPoint(int &xStart, int &yStart, int xDest, int yDest, int velocity);

	SDL_Rect getRect();

	void changeContent(const char* text);
	void explode();
	const char* getContentAt(int index) { return word->at(index); }
	const char* getContent() { return word->getContent(); }

	void setSelected() { selected = true; }
	void removeSelected() { selected = false; }
	bool isSelected() { return selected; }
	bool isEmpty() { return empty; }

private:
	bool selected = false;
	bool empty = false;

	int xpos;
	int ypos = -50;
	int deathStar_w = 70;
	int deathStar_h = 70;

	SDL_Renderer* renderer;
	FontManager* word;
	GameObject* DeathStar;
};
