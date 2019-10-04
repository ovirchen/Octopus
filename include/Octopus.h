//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#ifndef OCTOPUS_OCTOPUS_H
#define OCTOPUS_OCTOPUS_H

#include "Header.h"

class Octopus {

public:

    Octopus(SDL_Renderer *renderer);
    ~Octopus();

    void draw();
    void pushOff();
    void jump();
    void landing();
    void checkPosition(int xMap, int yMap);


private:
    int             x;
    int             y;
    int             w;
    int             h;
    SDL_Texture*    texture;
    int             frames;
    std::string     path;
};


#endif //OCTOPUS_OCTOPUS_H
