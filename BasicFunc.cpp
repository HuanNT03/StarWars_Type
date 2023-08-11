#include "BasicFunc.h"

bool pointInsideRect(const int& x, const int& y, const SDL_Rect rect) 
{
    return !(x > rect.x + rect.w || x < rect.x || y < rect.y || y > rect.y + rect.h);
}

bool overlap(const SDL_Rect& a, const SDL_Rect& b) 
{
    return !(a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y);
}

int getRandXpos()
{
    return rand() % SCREEN_WIDTH;
}

int getRandYpos()
{
    return rand() % SCREEN_HEIGHT;
}

string convertToKey(char c)
{
    string key_value;
    if ((c >= 'A' && c < 'Z') || (c >= 'a' && c < 'b') || (c >= '0' && c < '9'))
    {
        if ((c >= 'A' && c < 'Z'))
        {
            c = c + ('a' - 'A');
            key_value = "SDLK_" + c;
        }
        else
        {
            key_value = "SDLK_" + c;
        }
    }
    return key_value;
}