//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#ifndef OCTOPUS_GAME_H
#define OCTOPUS_GAME_H

#include "Header.h"


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

    class SDLException: public std::exception
    {
    public:
        SDLException();
        SDLException(SDLException const &src);
        ~SDLException() throw();
        SDLException &operator=(SDLException const &src);

        char const *what() const throw();
    };


private:
    int                 mouseX;
    int                 mouseY;
    SDL_Window	        *win;
    SDL_Renderer	    *renderer;
    SDL_Texture		    *texture;
    SDL_Event		    event;
    unsigned int	    *image;


};


#endif //OCTOPUS_GAME_H
