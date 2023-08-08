#include"StartScreen.h"
#include"BasicFunc.h"

StartScreen::StartScreen(SDL_Renderer* ren)
{
	renderer = ren;

	background = new BackGround(BACKGROUND_PATH, ren);

	gameLogo = new GameObject(LOGO_PATH, ren, (SCREEN_WIDTH - 400) / 2, 0, 400, 300);

	mainTheme = new AudioManager();
	mainTheme->loadMusic(MUSIC_PATH);
	mainTheme->playMusic();

	gameTitle = new FontManager(FONT_PATH_2, ren, 60, 255, 255, 255);
	gameTitle->loadRenderedText("_________TYPING GAME_________");
	gameTitle->update((SCREEN_WIDTH - gameTitle->getWidth()) / 2, 260);

	startButton = new FontManager(FONT_PATH, ren, 50, 255, 255, 255);
	startButton->loadRenderedText("START");
	startButton->update((SCREEN_WIDTH - startButton->getWidth()) / 2, 400);

	currentButton = NONE;
}

StartScreen::~StartScreen()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	delete background;
	delete mainTheme;
	delete startButton;
}


void StartScreen::show()
{
	background->render();
	gameLogo->render();
	gameTitle->render();
	startButton->render();
}

void StartScreen::handleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		SDL_MouseMotionEvent mouse = event.motion;

		if (pointInsideRect(mouse.x, mouse.y, startButton->getRect()))
		{
			startButton->changeColor(255, 232, 31);//yellow(255, 232, 31)
		}
		else
		{
			startButton->changeColor(255, 255, 255);
		}
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		SDL_MouseButtonEvent mouse = event.button;
		if (mouse.button == SDL_BUTTON_LEFT)
		{
			if (pointInsideRect(mouse.x, mouse.y, startButton->getRect()))
			{
				currentButton = START_BUTTON;// pay attention to this!!!! may cost error???
			}
		}
		
	}

	default:
		break;
	}
}
