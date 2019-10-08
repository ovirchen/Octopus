
#include "Move.h"

Move::Move() {}

Move::~Move() {}

void Move::pushOff(double x, double y)
{
    const int   frameDelay = 15000 / FPS;
    const int   len = 3;

    int i = 0;
    x = x / len;
    y = y / len;
    while (++i <= len) {
        frameStart = SDL_GetTicks();
        display(x, y, 1 + i);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}

void Move::pull(int i, double x, double y)
{
    int         FD = 3000;
    int         frameDelay;

    frameStart = SDL_GetTicks();
    display(x, y, 5);
    FD += 500 * i / 2;
    frameDelay = FD / FPS;
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
}

void Move::push(double x, double y)
{
    const int   FD = 10000;
    int         frameDelay = FD / FPS;
    const int   len = 3;
    int         j = 0;

    frameStart = SDL_GetTicks();
    x = x / len;
    y = y / len;
    while (++j <= len) {
        display(x, y, 6 + (j % 2));
    }
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
}


void Move::landing(double x, double y) {
    const int   frameDelay = 10000 / FPS;
    const int   len = 3;
    int         i = -1;

    x = x / len;
    y = y / len;
    while (++i < len) {
        frameStart = SDL_GetTicks();
        display(x, y, 7 + i);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}
