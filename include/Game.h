//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#ifndef OCTOPUS_GAME_H
#define OCTOPUS_GAME_H

#include "Header.h"

class Octopus;


class Game {

public:
    bool run;

    Game();
    ~Game();

    void init();
    void handleEvent();
    void update();
    void render();
    SDL_Renderer *getRenderer();

private:
    int                 mouseX;
    int                 mouseY;
    SDL_Window	        *win;
    SDL_Renderer	    *renderer;
    SDL_Texture		    *texture;
    SDL_Event		    event;
    std::unique_ptr<Octopus> oct;


};


#endif //OCTOPUS_GAME_H
