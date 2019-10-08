
#ifndef OCTOPUS_OCTOPUS_H
#define OCTOPUS_OCTOPUS_H

#include "Animation.h"

class Octopus : public Animation {

public:
    Octopus();
    ~Octopus();

    int     getPosX();
    int     getPosY();
//    void    setRenderer(SDL_Renderer *render);
    void    update(coordI mouse);
    void    draw();
    void    move(int i, double x, double y);
    void    pushOff(double x, double y);
    void    push(double x, double y);
    void    jump();
    void    landing(double x, double y);
    void    checkPosition(int map_x, int map_y);
//    void    changeImage(int i);
    void    findNextPush();

private:
    coordD          pos;
    coordD          dest;
    coordD          nextPush;
    coordI          mouseOct;
    int             width;
    int             height;
//    SDL_Surface     *image;
//    SDL_Rect        destRect;
//    SDL_Renderer    *renderer;
    Uint32          frameStart;
    int             frameTime;
};

#endif //OCTOPUS_OCTOPUS_H
