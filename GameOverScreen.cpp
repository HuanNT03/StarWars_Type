#include "GameOverScreen.h"

using std::cout;
using std::endl;
using std::to_string;

GameOverScreen::GameOverScreen(SDL_Renderer* ren, Uint32 score, bool win, bool newRecord)
{
	renderer = ren;
	winState = win;
	string score_statement = "Your score is: " + to_string(score);

	background = new BackGround(BACKGROUND_PATH, ren);

	gameLogo = new GameObject(LOGO_PATH, ren, (SCREEN_WIDTH - 200) / 2, 0, 200, 150);

	gameStatement[0] = new FontManager(FONT_PATH, ren, 90, 255, 255, 255);
	gameStatement[1] = new FontManager(FONT_PATH_2, ren, 25, 255, 255, 255);
	if (win)
	{
		gameStatement[0]->loadRenderedText("YOU WIN!!!");
	}
	else
	{
		if (newRecord)
		{
			gameStatement[0]->loadRenderedText("NEW HIGHSCORE!!!");
		}
		else
		{
			gameStatement[0]->loadRenderedText("GAMEOVER");
		}
		
	}
	
	gameStatement[0]->update((SCREEN_WIDTH - gameStatement[0]->getWidth()) / 2, 260);

	gameStatement[1]->loadRenderedText(score_statement.c_str());
	gameStatement[1]->update((SCREEN_WIDTH - gameStatement[1]->getWidth()) / 2, 350);

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
	gameStatement[0]->render(); 
	gameStatement[1]->render();
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
