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

    void draw(SDL_Renderer *renderer);
    void pushOff();
    void jump();
    void landing();
    void checkPosition(int xMap, int yMap);


private:
    int             x{0};
    int             y{0};
    int             w;
    int             h;
    SDL_Surface     *image;
    int             frames;
    std::string     path;
};


#endif //OCTOPUS_OCTOPUS_H
