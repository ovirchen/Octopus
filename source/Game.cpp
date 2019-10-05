//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#include "../include/Game.h"

Game::Game() {
    run = true;
}
Game::~Game() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    IMG_Quit();
    cout << "GamE OveR\n";
}

void Game::init()
{
    try {
        if ((SDL_Init(SDL_INIT_VIDEO) == -1) || (IMG_Init(IMG_INIT_PNG) == -1) ||
        (win = SDL_CreateWindow("Octopus", 0, 0, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)) == NULL)
            throw SDLException();
        if ((renderer = SDL_CreateRenderer(win, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
            throw SDLException();
        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255);
        if ((texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
                SDL_TEXTUREACCESS_TARGET, WIN_X, WIN_Y)) == NULL)
            throw SDLException();

        std::cout << "INIT EVERYTHING" << std::endl;

    }
    catch (SDLException e)
    {
        cout << SDL_GetError();
    }

}

void Game::handleEvent()
{
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            run = false;
        if (event.button.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            mouseX = 0;
            mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            cout << "MOUSE " << mouseX << " " << mouseY << "\n";
        }
    }
}

void Game::update(){}
void Game::render()
{
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}


Game::SDLException::SDLException() {}
Game::SDLException::SDLException(SDLException const &src) { *this = src; }
Game::SDLException::~SDLException() throw() { }
Game::SDLException& Game::SDLException::operator=(SDLException const &src) {
    std::exception::operator=(src);
    return *this;
}
char const* Game::SDLException::what() const throw() {
    return ("SDL ERROR\n");
}

