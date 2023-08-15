#pragma once

#include<cstdlib>
#include<string>
#include<math.h>
#include "SDL.h"
#include "config.h"

using std::string;


bool pointInsideRect(const int& x, const int& y, const SDL_Rect rect); 

bool overlap(const SDL_Rect& a, const SDL_Rect& b);

int getRandXpos();

int getRandYpos();

string convertToKey(char c);

double findAngle(double sin);
