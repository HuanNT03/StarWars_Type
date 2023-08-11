#include "Enemy.h"
#include "config.h"
#include "BasicFunc.h"

Enemy::Enemy(SDL_Renderer* ren, const char* text)
{
	renderer = ren;
	xpos = getRandXpos();

	word = new FontManager(FONT_PATH_2, ren, 24, 255, 255, 255);
	word->loadRenderedText(text);
	word->update(xpos, ypos - word->getHeight());

	DeathStar = new GameObject(DEATH_STAR_PATH, ren, xpos, ypos, deathStar_w, deathStar_h);

}

Enemy::~Enemy()
{
	if (empty!= true)
	{
		if (word != NULL)
		{
			delete word;
			word = NULL;
		}
	}

	delete DeathStar;
	DeathStar = NULL;
}

void Enemy::update()
{
	if (empty != true)
	{
		moveToPoint(xpos, ypos, (SCREEN_WIDTH - deathStar_w) / 2, SCREEN_HEIGHT - deathStar_h, VELOCITY);
		word->update(xpos, ypos - word->getHeight());
		DeathStar->update(xpos, ypos);
		if (selected)
		{
			word->changeColor(255, 232, 31);
		}
	}
	else
	{

	}
}

void Enemy::render()
{
	if (empty != true)
	{
		word->render();
	}
	
	DeathStar->render();
}

SDL_Rect Enemy::getRect()
{
	return DeathStar->getRect();
}

void Enemy::moveToPoint(int& xStart, int& yStart, int xDest, int yDest, int velocity)
{
	int xDistance = abs(xDest - xStart);
	int yDistance = abs(yDest - yStart);
	double distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));

	double sin = yDistance / distance;
	double cos = xDistance / distance;

	if (yDest > yStart)
	{
		yStart += int(velocity * sin);
	}
	else if (yDest < yStart)
	{
		yStart -= int(velocity * sin);
	}


	if (xDest > xStart)
	{
		xStart += int(velocity * cos);
	}
	else if (xDest < xStart)
	{
		xStart -= int(velocity * cos);
	}
}

void Enemy::changeContent(const char* text)
{
	if (string(text).length() != 0) 
	{
		word->loadRenderedText(text);
	}
	else
	{
		empty = true;
		selected = false;
		explode();
	}
}

void Enemy::explode()
{
	/*if (word != NULL)
	{
		delete word;
		word = NULL;
	}*/
	
	delete DeathStar;
	DeathStar = new GameObject(EXPLODE_PATH, renderer, xpos, ypos, deathStar_w, deathStar_h);
}