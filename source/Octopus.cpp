//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#include "../include/Octopus.h"


Octopus::Octopus(SDL_Renderer *renderer) {
    path = "../images/octopus1.jpg";
    w = 48;
    h = 27;
    checkPosition(678, 567);

    SDL_Surface *image;
    if (!(image = IMG_Load("carpet.png")))
    {
        cout << SDL_GetError() << "\n";
    }

//    SDL_RenderCopy(renderer, texture, NULL, NULL);
//    SDL_RenderPresent(renderer);

    this->frames = 4;
}
Octopus::~Octopus() {}

void Octopus::draw() {
    SDL_Rect    clips[frames];

    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = 48;
    clips[0].h = 27;

    clips[1].x = 48;
    clips[1].y = 0;
    clips[1].w = 48;
    clips[1].h = 27;

    clips[2].x = 96;
    clips[2].y = 0;
    clips[2].w = 48;
    clips[2].h = 27;

    clips[3].x = 144;
    clips[3].y = 0;
    clips[3].w = 48;
    clips[3].h = 27;
}
void Octopus::pushOff() {}
void Octopus::jump() {}
void Octopus::landing() {}

void Octopus::checkPosition(int xMap, int yMap) {
    this->x = xMap - this->w / 2;
    this->y = yMap - this->h / 2;
}