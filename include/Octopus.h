
#ifndef OCTOPUS_OCTOPUS_H
#define OCTOPUS_OCTOPUS_H

#include "Header.h"

class Octopus {

public:
    Octopus();
    ~Octopus();

    int     getPosX();
    int     getPosY();
    void    setRenderer(SDL_Renderer *render);
    void    update(int destX, int destY);
    void    draw();
    void    move(int i, double x, double y);
    void    pushOff(double x, double y);
    void    push(double x, double y);
    void    jump();
    void    landing(double x, double y);
    void    checkPosition(int xMap, int yMap);
    void    changeImage(int i);
    void    findNextPos();

private:
    double          pos_x;
    double          pos_y;
    double          dest_x;
    double          dest_y;
    double          next_x;
    double          next_y;
    int             mouse_x;
    int             mouse_y;
    int             width;
    int             height;
    SDL_Surface     *image;
    SDL_Rect        destRect;
    SDL_Renderer    *renderer;
    Uint32          frameStart;
    int             frameTime;
};

#endif //OCTOPUS_OCTOPUS_H
