
#include "Draw.h"


Draw::Draw() : width{144}, height{81} {
    std::string str;
    for (int i = 1; i <= 9; i++) {
        str = "./Assets/img/00" + std::to_string(i) + ".png";
        images.push_back(IMG_Load(str.c_str()));
    }
    curImage = images[0];
    destRect.w = width;
    destRect.h = height;
}

Draw::~Draw() {
    for(auto & img : images){ SDL_FreeSurface(img); }
}

void Draw::setRenderer(SDL_Renderer *render) { renderer = render; }
int Draw::getWidth() { return width; }
int Draw::getHeight() { return height; }

void Draw::changeImage(int i) {
    if (i > 9 || i < 1)
        return ;
    curImage = images[i - 1];
}

void Draw::draw(coordD pos) {
    SDL_RenderClear(renderer);
    destRect.x = pos.x;
    destRect.y = pos.y;
    auto local_texture = SDL_CreateTextureFromSurface(renderer, curImage);
    SDL_RenderCopy(renderer, local_texture, NULL, &destRect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(local_texture);
}