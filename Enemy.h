#pragma once

#include "Game.h"
#include "GameObject.h"
#include "FontManager.h"

class Enemy
{
public:
	Enemy(SDL_Renderer* ren, const char* text);
	~Enemy();

	void update(int x, int y);
	void render();

	SDL_Rect getRect();

	void setSelected() { isSelected = true; }
	bool selected() { return isSelected; }
	bool empty() { return isEmpty; }

private:
	bool isSelected = false;
	bool isEmpty = false;

	int xStartPos;
	int yStartPos = 50;
	int deathStar_w = 70;
	int deathStar_h = 70;

	SDL_Renderer* renderer;
	FontManager* word;
	GameObject* DeathStar;
};
