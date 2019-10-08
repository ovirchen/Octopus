
#ifndef OCTOPUS_GAME_H
#define OCTOPUS_GAME_H

#include "Header.h"
#include "Octopus.h"



class Octopus;

class Game {

public:
    bool run;

    Game();
    ~Game();

    SDL_Renderer    *getRenderer();
    void            init();
    void            handleEvent();
    void            render();

private:
    coordI                      mouse;
    SDL_Window                  *win;
    SDL_Renderer                *renderer;
    SDL_Texture	                *texture;
    SDL_Event	                event;
    std::unique_ptr<Octopus>    oct;

};


#endif //OCTOPUS_GAME_H
