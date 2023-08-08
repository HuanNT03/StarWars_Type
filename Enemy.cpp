#include "Enemy.h"
#include "config.h"
#include "BasicFunc.h"

Enemy::Enemy(SDL_Renderer* ren, const char* text)
{
	renderer = ren;
	xStartPos = getRandXpos();

	word = new FontManager(FONT_PATH, ren, 24, 255, 255, 255);
	word->loadRenderedText(text);
	word->update(xStartPos, yStartPos - word->getHeight());

	DeathStar = new GameObject(DEATH_STAR_PATH, ren, xStartPos, yStartPos, deathStar_w, deathStar_h);

}

Enemy::~Enemy()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
}

void Enemy::update(int x, int y)
{
	yStartPos += VELOCITY;
	word->update(xStartPos, yStartPos - word->getHeight());
	DeathStar->update(xStartPos, yStartPos);
	if (isEmpty) {

	}
}

void Enemy::render()
{
	word->render();
	DeathStar->render();
}

SDL_Rect Enemy::getRect()
{
	return DeathStar->getRect();
}