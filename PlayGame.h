#pragma once

#include <vector>
#include "Game.h"
#include "Enemy.h"
#include "BackGround.h"
#include "FontManager.h"
#include "AudioManager.h"
#include "FileManager.h"
#include "config.h"

using std::vector;
using std::to_string;



class PlayGame
{
public:
	PlayGame(SDL_Renderer* ren, bool loop);
	~PlayGame();

	void update();
	void render();
	void handleEvent(SDL_Event& event);
	void createEnemy();
	bool isSelected();
	void deleteEnemy();

	Uint32 getTimer() { return Timer; }
	bool overState() { return isGameOver; }
	bool winState() { return isWin; }

private:

	bool loop;
	bool isWin = false;
	bool isGameOver = false;
	bool isCreatedEnemy;
	bool isNewGame;
	int timeGap = SPAWN_TIME; //thoi gian khoi tao enemy moi
	int spaceShip_w = 100;
	int spaceShip_h = 100;
	int quote_index;
	int selectedIndex;

	Uint32 your_score;
	Uint32 Timer = 0;
	Uint32 startGameTime = 0;
	//vector<int> countDown; 


	SDL_Renderer* renderer;
	BackGround* background;
	vector<Enemy*> deathStar;
	GameObject* spaceShip;
	AudioManager* shoottingEffect;
	AudioManager* explodeEffect;
	AudioManager* errorEffect;
	FontManager* yourScore[2];
	FontManager* highScore[2];

	vector<string> quote;

};

