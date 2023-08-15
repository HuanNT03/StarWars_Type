#pragma once

#include <vector>
#include "Game.h"
#include "Enemy.h"
#include "BackGround.h"
#include "FontManager.h"
#include "AudioManager.h"
#include "FileManager.h"
#include "Laser.h"
#include "config.h"

using std::vector;
using std::to_string;
using std::stoul;
using std::stringstream;

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
	bool newRecord() { return newHighScore; }
	Uint32 getScore() { return your_score; }

private:

	bool loop;
	bool isWin = false;
	bool isGameOver = false;
	bool isCreatedEnemy;
	bool isNewGame;
	bool newHighScore;
	bool paused;
	int timeGap = SPAWN_TIME; //thoi gian khoi tao enemy moi
	int spaceShip_w = 100;
	int spaceShip_h = 100;
	int quote_index;
	int selectedIndex;
	//int currentButton;
	string timeText;

	Uint32 your_score;
	Uint32 high_score;
	Uint32 Timer = 0;
	Uint32 startGameTime = 0;
	Uint32 pauseGameTime = 0;
	//vector<int> countDown; 


	SDL_Renderer* renderer;
	BackGround* background;
	vector<Enemy*> deathStar;
	GameObject* spaceShip;
	GameObject* pauseButton;
	AudioManager* shoottingEffect;
	AudioManager* explodeEffect;
	AudioManager* errorEffect;
	FontManager* yourScore[2];
	FontManager* highScore[2];
	FontManager* clock;
	FontManager* screenPause;

	vector<string> quote;
	vector<Laser*> bullet;

};

