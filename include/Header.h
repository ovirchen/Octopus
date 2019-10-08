
#ifndef OCTOPUS_HEADER_H
#define OCTOPUS_HEADER_H

#define WIN_X 1920
#define WIN_Y 1080
#define FPS 60

#include "../frameworks/SDL2.framework/Headers/SDL.h"
#include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include <exception>
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <cmath>

struct  coordD
{
    double x;
    double y;
};

struct  coordI
{
    int x;
    int y;
};

//#include "Animation.h"
#include "Octopus.h"
#include "Game.h"


using namespace std;


#endif //OCTOPUS_HEADER_H
