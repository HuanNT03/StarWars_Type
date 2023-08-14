#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "AudioManager.h"
#include "BackGround.h"
#include "FontManager.h"
#include "StartScreen.h"
#include "FileManager.h"
#include "PlayGame.h"
#include "GameOverScreen.h"
#include "config.h"

using std::cout;
using std::endl;



AudioManager* clickSound;

StartScreen* startScreen = nullptr;
PlayGame* playGame;
GameOverScreen* gameOverScreen;


Game::Game()
{
	count = 0;
	window = NULL;
	renderer = NULL;
	isRunning = true; // take notice about this variable
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	srand(time(0));
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		isRunning = false;
	}
	else 
	{
		cout << "SDL initialize!... " << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window == NULL)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		}
		else
		{
			cout << "Window created!" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		//ren = renderer;
		if (renderer == NULL)
		{
			cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
		}
		else
		{
			cout << "SDl_mixer initialize!" << endl;
		}
		if (TTF_Init() == -1)
		{
			cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
		}
		else
		{
			cout << "SDL_ttf initialize!" << endl;
		}

		isRunning = true;
		inStartScreen = true;
		isPlaying = false;
		GameOver = false;

		clickSound = new AudioManager();
		clickSound->loadSoundEffect("audio/mouse-click.mp3");

		startScreen = new StartScreen(renderer);

		playGame = new PlayGame(renderer, GAME_LOOP);

		//gameOverScreen = new GameOverScreen(renderer, playGame->winState());


		/*data = new FileManager(THE_CAT_IN_THE_HAT_PATH);
		data->getData();*/

	}

	

	/*themeSong = new AudioManager();
	themeSong->loadMusic("audio/Star_Wars_Main_Theme_Song.mp3");
	themeSong->playMusic();*/



}

void Game::handleEvents()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if (inStartScreen)
		{
			startScreen->handleEvents(event);
		}
		else if (isPlaying)
		{
			playGame->handleEvent(event);
		}
		else if (GameOver)
		{
			gameOverScreen->handleEvents(event);
		}
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			SDL_MouseButtonEvent mouse = event.button;
			clickSound->playSoundEffect();
			/*text->changeColor(0, 0, 0);*/
			if (mouse.button == SDL_BUTTON_LEFT) {
				printf("Left button pressed at (%d, %d)\n", mouse.x, mouse.y);
			}
			break;
		}

		default:
			break;
		}
	}
}

void Game::update()
{
	/*player->update();
	text->update((SCREEN_WIDTH - text->getWidth()) / 2, 200);*/
	if (inStartScreen)
	{
		currentButton = startScreen->getCurrentButton();
		if (currentButton == START_BUTTON) 
		{

			isPlaying = true;
			inStartScreen = false;
			currentButton = NONE;
			startScreen->resetButton();

		}
	}
	if (isPlaying)
	{
		if (currentButton == RETRY_BUTTON)
		{
			
			currentButton = NONE;
		}
		playGame->update();
		if (playGame->overState())
		{
			isPlaying = false;
			GameOver = true;
			currentButton = GAME_OVER;
		}
	}
	if (GameOver)
	{
		if (currentButton == GAME_OVER)
		{
			gameOverScreen = new GameOverScreen(renderer, playGame->winState());
			currentButton = NONE;
		}
		currentButton = gameOverScreen->getCurrentButton();
		if (currentButton == RETRY_BUTTON)
		{
			delete playGame;
			playGame = new PlayGame(renderer, GAME_LOOP);
			gameOverScreen->resetButton();
			GameOver = false;
			isPlaying = true;
		}
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	/*background->render();
	player->render();
	text->render();*/
	if (inStartScreen)
	{
		startScreen->show();
	}
	else if (isPlaying)
	{
		playGame->render();
	}
	else if (GameOver)
	{
		gameOverScreen->show();
	}
	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;


	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
	
	cout << "Game cleaned!" << endl;
}