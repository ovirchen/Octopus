
#ifndef OCTOPUS_ANIMATION_H
#define OCTOPUS_ANIMATION_H

#include "Header.h"

class Animation {

public:

    Animation();
    ~Animation();

    void    setRenderer(SDL_Renderer *render);
    void    setDestRect(int width, int height);
    void    changeImage(int i);
    void    draw(coordD pos);

private:
    int             width;
    int             height;
    SDL_Surface     *image;
    SDL_Rect        destRect;
    SDL_Renderer    *renderer;
};


#endif //OCTOPUS_ANIMATION_H
