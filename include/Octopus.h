//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#ifndef OCTOPUS_OCTOPUS_H
#define OCTOPUS_OCTOPUS_H

#include "Header.h"

class Octopus {

public:

    Octopus();
    ~Octopus();

    void    setRenderer(SDL_Renderer *render);
    int     getPosX();
    int     getPosY();
    void    update(int destX, int destY);
    void    draw();
    void    move(int i, int len, double x, double y);
    void    pushOff(double x, double y);
    void    jump();
    void    landing(double x, double y);
    void    checkPosition(int xMap, int yMap);


private:
    double             pos_x{0};
    double             pos_y{0};
    double             dest_x;
    double             dest_y;
    int             width;
    int             height;
    SDL_Surface     *image;
    SDL_Rect        srcRect, destRect;
    SDL_Renderer    *renderer;
};

#endif //OCTOPUS_OCTOPUS_H
