
#include "Animation.h"

Animation::Animation() {
    if (!(image = IMG_Load(R"(./Assets/img/0001.png)"))) {
        std::cout << SDL_GetError() << std::endl;
        std::cout << "Try again" << std::endl;
        exit(1);
    }
}

Animation::~Animation() {
    SDL_FreeSurface(image);
}

void Animation::setRenderer(SDL_Renderer *render) {
    renderer = render;
}

void Animation::setDestRect(int width, int height)
{
    destRect.w = width;
    destRect.h = height;
}

void Animation::changeImage(int i) {
    std::string str;

    if (i < 10) {
        str = "./Assets/img/000" + std::to_string(i) + ".png";
        SDL_FreeSurface(image);
        image = IMG_Load(str.c_str());
    }
    else
    {
        str = "./Assets/img/00" + std::to_string(i) + ".png";
        SDL_FreeSurface(image);
        image = IMG_Load(str.c_str());
    }
}

void Animation::draw(coordD pos) {
    SDL_RenderClear(renderer);
    destRect.x = pos.x;
    destRect.y = pos.y;
    auto local_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, local_texture, NULL, &destRect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(local_texture);
}