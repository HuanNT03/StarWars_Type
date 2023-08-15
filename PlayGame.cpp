#include "PlayGame.h"
#include "BasicFunc.h"


PlayGame::PlayGame(SDL_Renderer* ren, bool _loop)
{
	loop = _loop;
	isWin = false;
	quote_index = 0;
	isCreatedEnemy = true;
	isNewGame = true;
	selectedIndex = -1;
	your_score = 0;
	newHighScore = false;
	paused = false;
	timeText = "Timer: " + to_string(Timer / 1000.f);
	timeText.erase(timeText.end() - 3, timeText.end());

	renderer = ren;

	background = new BackGround(BACKGROUND_2_PATH, ren);

	spaceShip = new GameObject(SHIP_PATH, ren, (SCREEN_WIDTH-spaceShip_w) / 2, (SCREEN_HEIGHT-spaceShip_h), spaceShip_w, spaceShip_h);

	pauseButton = new GameObject(PAUSE_BUTTON_PATH, ren, (SCREEN_WIDTH - 50) / 2, 10, 50, 50);

	shoottingEffect = new AudioManager();
	shoottingEffect->loadSoundEffect(FIRING_SOUND_EFFECT);

	errorEffect = new AudioManager();
	errorEffect->loadSoundEffect(ERROR_SOUND_PATH);

	explodeEffect = new AudioManager();
	explodeEffect->loadSoundEffect(EXPLODE_SOUND_PATH);

	clock = new FontManager(FONT_PATH_2, ren, 20, 255, 255, 255);
	clock->loadRenderedText(timeText.c_str());
	clock->update(10, SCREEN_HEIGHT - (clock->getHeight() + 5));

	highScore[0] = new FontManager(FONT_PATH, ren, 20, 255, 255, 255);
	highScore[0]->loadRenderedText("HIGH SCORE: ");
	highScore[0]->update(10, 10);

	FileManager* tmp_high_score;
	tmp_high_score = new FileManager(HIGH_SCORE_PATH);
	if (tmp_high_score->getSize() == 0)
	{
		high_score = 0;
	}
	else
	{
		high_score = stoul(tmp_high_score->getDataAt(0), nullptr, 10);
	}
	delete tmp_high_score;

	highScore[1] = new FontManager(FONT_PATH, ren, 20, 255, 255, 255);
	highScore[1]->loadRenderedText(to_string(high_score).c_str());
	highScore[1]->update(highScore[0]->getWidth() + 10, 10);

	yourScore[0] = new FontManager(FONT_PATH, ren, 20, 255, 255, 255);
	yourScore[0]->loadRenderedText("YOUR SCORE: ");
	yourScore[0]->update(10, highScore[0]->getHeight() + 15);
	
	yourScore[1] = new FontManager(FONT_PATH, ren, 20, 255, 255, 255);
	yourScore[1]->loadRenderedText(to_string(your_score).c_str());
	yourScore[1]->update(yourScore[0]->getWidth() + 10, highScore[0]->getHeight() + 15);

	screenPause = new FontManager(FONT_PATH, ren, 60, 255, 232, 31);
	screenPause->loadRenderedText("GAME PAUSED");
	screenPause->update((SCREEN_WIDTH - screenPause->getWidth()) / 2, (SCREEN_HEIGHT - screenPause->getHeight()) / 2);

	FileManager* tempQuote = new FileManager(THE_CAT_IN_THE_HAT_PATH);
	quote = tempQuote->getData();

	delete tempQuote;
	tempQuote = NULL;
}

PlayGame::~PlayGame()
{
	delete background;
	background = NULL;

	for (int i = 0; i < deathStar.size(); i++)
	{
		delete deathStar.at(i);
		deathStar.at(i) = NULL;
	} ///// hoi thay 
	deathStar.clear();

	delete spaceShip;
	spaceShip = NULL;

	delete shoottingEffect;
	shoottingEffect = NULL;

	delete clock;
	clock = NULL;

	delete yourScore[0];
	delete yourScore[1];
	yourScore[0] = NULL;
	yourScore[1] = NULL;

	delete highScore[0];
	delete highScore[1];
	highScore[0] = NULL;
	highScore[1] = NULL;

	delete pauseButton;
	pauseButton = NULL;
}


void PlayGame::update()
{
	static int timeGapCount = 0;
	if (isNewGame)
	{
		timeGapCount = 0;
		startGameTime = SDL_GetTicks();
		isNewGame = false;
	}
	
	if (!paused)
	{
		Timer = SDL_GetTicks() - startGameTime;

		if (isCreatedEnemy)
		{
			if ((Timer) >= timeGap * timeGapCount)
			{
				createEnemy();
				timeGapCount++;
			}
		} ///su dung thoi gian

		/*if (isCreatedEnemy)
		{
			Timer++;
			if (Timer % 120 == 0) {
				createEnemy();
			}
		}*/

		deleteEnemy();

		for (int i = 0; i < deathStar.size(); i++)
		{
			if (overlap(deathStar.at(i)->getRect(), spaceShip->getRect()))
			{
				if (high_score < your_score)
				{
					high_score = your_score;

					newHighScore = true;

					FileManager* tmp_high_score;
					tmp_high_score = new FileManager(HIGH_SCORE_PATH);
					tmp_high_score->writeFile(to_string(high_score));
					delete tmp_high_score;
				}
				isWin = false;
				isGameOver = true;
			}
			deathStar.at(i)->update();
		}

		for (int j = 0; j < bullet.size(); j++)
		{
			if (selectedIndex != -1)
			{
				if (overlap(bullet.at(j)->getRect(), deathStar.at(selectedIndex)->getRect()))
				{
					bullet.erase(bullet.begin() + j);
				}
				else
				{
					bullet.at(j)->update((deathStar.at(selectedIndex)->getRect().x) + (deathStar.at(selectedIndex)->getRect().w / 2), (deathStar.at(selectedIndex)->getRect().y) + (deathStar.at(selectedIndex)->getRect().h / 2));
				}
			}
			else 
			{
				bullet.clear();
			}
		}

		if (!isCreatedEnemy && deathStar.size() == 0)
		{
			if (high_score < your_score)
			{
				high_score = your_score;

				newHighScore = true;

				FileManager* tmp_high_score;
				tmp_high_score = new FileManager(HIGH_SCORE_PATH);
				tmp_high_score->writeFile(to_string(high_score));
				delete tmp_high_score;
			}
			isWin = true;
			isGameOver = true;
		}
	}
	else
	{
		Timer = pauseGameTime;
	}

	timeText = "Timer: " + to_string(Timer / 1000.f);
	timeText.erase(timeText.end() - 3, timeText.end());
	clock->loadRenderedText(timeText.c_str());
}

void PlayGame::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	{
		SDL_MouseButtonEvent mouse = event.button;

		if (pointInsideRect(mouse.x, mouse.y, pauseButton->getRect()))
		{
			if (paused)
			{
				paused = false;
				startGameTime = SDL_GetTicks() - pauseGameTime;
				pauseGameTime = 0;
			}
			else
			{
				paused = true;
				pauseGameTime = SDL_GetTicks() - startGameTime;
				startGameTime = 0;
			}
		}
	}

	case SDL_KEYDOWN:
	{
		if (!paused)
		{
			//string key_value = SDL_GetKeyName(event.key.keysym.sym);
			string letter;
			string newContent;
			if (!isSelected())
			{
				//cout << "1: " << endl;
				for (int i = 0; i < deathStar.size(); i++)
				{
					if (!deathStar.at(i)->isEmpty())
					{
						letter = *deathStar.at(i)->getContentAt(0); /// ???? tai sao so 0 lai bi "string subscript out of range"

						if (SDL_GetKeyFromName(letter.c_str()) == event.key.keysym.sym)
						{
							shoottingEffect->playSoundEffect();

							Laser* tmpBullet = new Laser(LASER_PATH, renderer, (SCREEN_WIDTH - 50) / 2, (SCREEN_HEIGHT - spaceShip_h - 50), 50, 50);
							bullet.push_back(tmpBullet);
							tmpBullet = nullptr;

							your_score++;
							yourScore[1]->loadRenderedText(to_string(your_score).c_str());

							deathStar.at(i)->setSelected();
							selectedIndex = i;
							newContent = string(deathStar.at(i)->getContent()).erase(0, 1);
							deathStar.at(i)->changeContent(newContent.c_str());
							if (deathStar.at(i)->isEmpty())
							{
								deathStar.at(i)->removeSelected();

								//explodeEffect->playSoundEffect();

								selectedIndex = -1;
							}
							break;
						}
						else if (SDL_GetKeyFromName(letter.c_str()) != event.key.keysym.sym)
						{
							errorEffect->playSoundEffect();
						}
					}

				}
			}
			else
			{
				//cout << "2: " << endl;
				letter = *deathStar.at(selectedIndex)->getContent();// const char* giống bên trên 

				if (event.key.keysym.sym == SDL_GetKeyFromName(letter.c_str()))
				{
					shoottingEffect->playSoundEffect();

					Laser* tmpBullet = new Laser(LASER_PATH, renderer, (SCREEN_WIDTH - 50) / 2, (SCREEN_HEIGHT - spaceShip_h - 50), 50, 50);
					bullet.push_back(tmpBullet);
					tmpBullet = nullptr;

					your_score++;
					yourScore[1]->loadRenderedText(to_string(your_score).c_str());

					newContent = string(deathStar.at(selectedIndex)->getContent()).erase(0, 1);
					deathStar.at(selectedIndex)->changeContent(newContent.c_str());
					if (deathStar.at(selectedIndex)->isEmpty())
					{
						deathStar.at(selectedIndex)->removeSelected();

						//explodeEffect->playSoundEffect();

						selectedIndex = -1;
					}
				}
				else if (SDL_GetKeyFromName(letter.c_str()) != event.key.keysym.sym)
				{
					errorEffect->playSoundEffect();
				}
			}
		}
		break;
	}
		
	default:
		break;
	}
}


void PlayGame::render()
{
	background->render();

	for (int i = 0; i < deathStar.size(); i++)
	{
		deathStar.at(i)->render();
	}

	for (int j = 0; j < bullet.size(); j++)
	{
		if (selectedIndex != -1)
		{
			bullet.at(j)->render();
		}
	}

	spaceShip->render();

	yourScore[0]->render();
	yourScore[1]->render();

	highScore[0]->render();
	highScore[1]->render();

	clock->render();

	pauseButton->render();
	if (paused)
	{
		screenPause->render();
	}
}

void PlayGame::createEnemy()
{
	if (quote_index < quote.size())
	{
		Enemy* tempEnemy;

		tempEnemy = new Enemy(renderer, (quote.at(quote_index)).c_str());
		deathStar.push_back(tempEnemy);

		tempEnemy = nullptr;
		quote_index++;

		isCreatedEnemy = true;
	}
	else if (quote_index >= quote.size())
	{
		if (loop == true) 
		{ 
			quote_index = 0;

			Enemy* tempEnemy;

			tempEnemy = new Enemy(renderer, (quote.at(quote_index)).c_str());
			deathStar.push_back(tempEnemy);

			tempEnemy = nullptr;

			quote_index++;

			isCreatedEnemy = true;
		}
		else
		{
			//Timer = -1;
			isCreatedEnemy = false;
		}
	}
}

bool PlayGame::isSelected()
{
	bool selected = false;
	if (selectedIndex == -1)
	{
		/*for (int i = 0; i < deathStar.size(); i++)
		{
			if (deathStar.at(i)->isSelected())
			{
				selected = true;
				selectedIndex = i;
				break;
			}
		}*/
		selected = false;
	}
	else
	{
		selected = true;
	}
	
	return selected;
}

void PlayGame::deleteEnemy()
{
	static int count_down = 6;
	for (int i = 0; i < deathStar.size(); i++)
	{
		if (deathStar.at(i)->isEmpty())
		{
			if (count_down == 0)
			{
				deathStar.erase(deathStar.begin() + i);
				count_down = 7;
			}
			count_down--;
		}
	}
}
