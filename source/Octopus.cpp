//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#include "../include/Octopus.h"


Octopus::Octopus() :w{100}, h{100}, path{"./Assets/img/octopus.png"} {
    checkPosition(678, 567);
    if (!(image = IMG_Load(path.c_str()))) {
        std::cout << SDL_GetError() << std::endl;
    }
    this->frames = 4;
}
Octopus::~Octopus() {
    SDL_FreeSurface(image);
}

void Octopus::draw(SDL_Renderer *renderer) {
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

    {
        SDL_Rect SrcR;
        SDL_Rect DestR;

        SrcR.x = 0;
        SrcR.y = 0;
        SrcR.w = w;
        SrcR.h = h;

        DestR.x = WIN_X / 2 - w / 2;
        DestR.y = WIN_Y / 2 - h / 2;
        DestR.w = w;
        DestR.h = h;

        auto local_texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, local_texture, &SrcR, &DestR);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(local_texture);
    }
}
void Octopus::pushOff() {}
void Octopus::jump() {}
void Octopus::landing() {}

void Octopus::checkPosition(int xMap, int yMap) {
    this->x = xMap - this->w / 2;
    this->y = yMap - this->h / 2;
}
