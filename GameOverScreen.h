#pragma once

#include "config.h"
#include "BasicFunc.h"
#include "Game.h"
#include "GameObject.h"
#include "BackGround.h"
#include "AudioManager.h"
#include "FontManager.h"

class GameOverScreen
{
public:
	GameOverScreen(SDL_Renderer* ren, bool win);
	~GameOverScreen();

	void show();
	void handleEvents(SDL_Event& event);

	int getCurrentButton() { return currentButton; }
	void resetButton() { currentButton = NONE; }

private:
	int currentButton;
	bool winState;
	SDL_Renderer* renderer;
	BackGround* background;
	GameObject* gameLogo;
	FontManager* retryButton;
	FontManager* gameStatement;
};

