#pragma once

#include<cstdlib>
#include "SDL.h"
#include "config.h"


bool pointInsideRect(const int& x, const int& y, const SDL_Rect rect); 

bool overlap(const SDL_Rect& a, const SDL_Rect& b);

int getRandXpos();

int getRandYpos();
