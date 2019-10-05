//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#include "../include/Octopus.h"


Octopus::Octopus() :width{144}, height{81} {
    checkPosition(600, 500);
    dest_x = pos_x;
    dest_y = pos_y;
    if (!(image = IMG_Load(R"(./Assets/img/0001.png)"))) {
        std::cout << SDL_GetError() << std::endl;
        std::cout << "Try again" << std::endl;
        exit(1);
    }
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;

    destRect.x = pos_x;
    destRect.y = pos_y;
    destRect.w = width;
    destRect.h = height;

}
Octopus::~Octopus() {
    SDL_FreeSurface(image);
}

void Octopus::setRenderer(SDL_Renderer *render) { renderer = render; }
int Octopus::getPosX() { return pos_x; }
int Octopus::getPosY() { return pos_y; }

void Octopus::update(int destX, int destY)
{
    dest_x = destX;
    dest_y = destY;

    jump();
}

void Octopus::draw() {
    {
//        cout << "\tdraw\n";
        SDL_RenderClear(renderer);
        destRect.x = pos_x;
        destRect.y = pos_y;
        auto local_texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, local_texture, NULL, &destRect);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(local_texture);
    }
}

void Octopus::move(int i, int len, double x, double y)
{
//    cout << "\tmove\n";
    const int   FPS = 60;
    int         FD = 5000;
    int         frameDelay = FD / FPS;
    Uint32      frameStart;
    int         frameTime;

    if (i == 0) {
        pushOff(x, y);
    }
    else if (i == len - 2) {
        landing(x, y);
    }
    else {
        frameStart = SDL_GetTicks();

        pos_y += y;
        pos_x += x;
        draw();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        frameDelay = FD / FPS;
        FD += 2000 * i;
    }

}

void Octopus::pushOff(double x, double y)
{
    const int   FPS = 60;
    const int   frameDelay = 15000 / FPS;
    Uint32      frameStart;
    int         frameTime;
    const int   len = 3;

    int i = -1;
    x = x / len;
    y = y / len;
    while (++i < len) {
        frameStart = SDL_GetTicks();
        pos_y += y;
        pos_x += x;
        draw();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

//    cout << "\tpushOff\n";
//    int frames = 6;
//    int speed = 100;
//    SDL_Rect    clips[frames];

//    srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

//    clips[0].x = 0;
//    clips[0].y = 0;
//    clips[0].w = width;
//    clips[0].h = height;
//
//    clips[1].x = width;
//    clips[1].y = 0;
//    clips[1].w = width;
//    clips[1].h = height;
//
//    clips[2].x = width * 2;
//    clips[2].y = 0;
//    clips[2].w = width;
//    clips[2].h = height;
//
//    clips[3].x = width * 3;
//    clips[3].y = 0;
//    clips[3].w = width;
//    clips[3].h = height;

}

void Octopus::jump()
{
//    cout << "\tjump\n";
    const int   len = 20;

    if (dest_x == pos_x && dest_y == pos_y)
        return;
    int del_x = 1;
    int del_y = 1;
    double gx = abs(dest_x - pos_x) / len;
    double gy = abs(dest_y - pos_y) / len;
    int i = -1;
    if (pos_x <= dest_x && pos_y <= dest_y) // 3
    {
        while(++i < len && pos_x <= dest_x && pos_y <= dest_y)
        {
            move(i, len, gx * del_x, gy * del_y);
        }
    }
    else if (pos_x <= dest_x && pos_y > dest_y) // 2
    {
        del_y = -1;
        while(++i < len && pos_x <= dest_x && pos_y >= dest_y)
        {
            move(i, len, gx * del_x, gy * del_y);
        }

    }
    else if (pos_x > dest_x && pos_y <= dest_y) // 4
    {
        del_x = -1;
        while(++i < len && pos_x >= dest_x && pos_y <= dest_y)
        {
            move(i, len, gx * del_x, gy * del_y);
        }
    }
    else  // 1
    {
        del_x = -1;
        del_y = -1;
        while(++i < len && pos_x >= dest_x && pos_y >= dest_y)
        {
            move(i, len, gx * del_x, gy * del_y);
        }
    }
//    checkPosition(dest_x, dest_y);
    pos_x = dest_x;
    pos_y = dest_y;
    }

void Octopus::landing(double x, double y) {
//    cout << "\tlanding\n";
    const int   FPS = 60;
    const int   frameDelay = 10000 / FPS;
    Uint32      frameStart;
    int         frameTime;
    const int   len = 3;

    int i = -1;
    x = x / len;
    y = y / len;
    while (++i < len) {
        frameStart = SDL_GetTicks();
        pos_y += y;
        pos_x += x;
        draw();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}

void Octopus::checkPosition(int xMap, int yMap) {
    this->pos_x = xMap - this->width / 2;
    this->pos_y = yMap - this->height / 2;
}
