#include "GameOverScreen.h"

using std::cout;
using std::endl;

GameOverScreen::GameOverScreen(SDL_Renderer* ren, bool win)
{
	renderer = ren;
	winState = win;

	background = new BackGround(BACKGROUND_PATH, ren);

	gameLogo = new GameObject(LOGO_PATH, ren, (SCREEN_WIDTH - 200) / 2, 0, 200, 150);

	gameStatement = new FontManager(FONT_PATH, ren, 90, 255, 255, 255);
	if (win)
	{
		gameStatement->loadRenderedText("YOU WIN!!!");
	}
	else
	{
		gameStatement->loadRenderedText("GAMEOVER");
	}
	
	gameStatement->update((SCREEN_WIDTH - gameStatement->getWidth()) / 2, 260);

	retryButton = new FontManager(FONT_PATH, ren, 50, 255, 255, 255);
	retryButton->loadRenderedText("RETRY");
	retryButton->update((SCREEN_WIDTH - retryButton->getWidth()) / 2, 400);

	currentButton = NONE;
};

GameOverScreen::~GameOverScreen()
{

}

void GameOverScreen::show()
{
	background->render();
	gameLogo->render();
	gameStatement->render();
	retryButton->render();
}

void GameOverScreen::handleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		SDL_MouseMotionEvent mouse = event.motion;

		if (pointInsideRect(mouse.x, mouse.y, retryButton->getRect()))
		{
			retryButton->changeColor(255, 232, 31);//yellow(255, 232, 31)
		}
		else
		{
			retryButton->changeColor(255, 255, 255);
		}
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		SDL_MouseButtonEvent mouse = event.button;
		if (mouse.button == SDL_BUTTON_LEFT)
		{
			if (pointInsideRect(mouse.x, mouse.y, retryButton->getRect()))
			{
				currentButton = RETRY_BUTTON;
			}
		}
	}

	default:
		break;
	}
}
