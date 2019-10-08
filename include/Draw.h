
#ifndef OCTOPUS_Draw_H
#define OCTOPUS_Draw_H

#include "Header.h"
#include <vector>

class Draw {

public:
    Draw();
    ~Draw();

    void    setRenderer(SDL_Renderer *render);
    int     getWidth();
    int     getHeight();
    void    changeImage(int i);
    void    draw(coordD pos);

private:
    int                         width;
    int                         height;
    std::vector<SDL_Surface*>   images;
    SDL_Surface                 *curImage;
    SDL_Rect                    destRect;
    SDL_Renderer                *renderer;
};


#endif //OCTOPUS_Draw_H
