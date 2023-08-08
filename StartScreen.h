#pragma once

#include "config.h"
//#include "Game.h"
#include "GameObject.h"
#include "BackGround.h"
#include "AudioManager.h"
#include "FontManager.h"


class StartScreen
{
public:
	StartScreen(SDL_Renderer* ren);
	~StartScreen();

	void show();
	void handleEvents(SDL_Event &event);
	int getCurrentButton() { return currentButton; }
	void resetButton() { currentButton = NONE; }

private:
	int currentButton;
	SDL_Renderer* renderer;
	BackGround* background;
	GameObject* gameLogo;
	AudioManager* mainTheme;
	FontManager* startButton;
	FontManager* gameTitle;

};

