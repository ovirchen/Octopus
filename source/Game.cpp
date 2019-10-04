//
// Created by Olga VIRCHENKO on 2019-10-02.
//

#include "../include/Game.h"

Game::Game() {
    run = true;
}
Game::~Game() {}

void Game::init()
{
    try {
        if ((SDL_Init(SDL_INIT_VIDEO) == -1) || (IMG_Init(IMG_INIT_PNG) == -1) ||
        (this->win = SDL_CreateWindow("Octopus", 0, 0, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)) == NULL)
            throw SDLException();
        if ((this->renderer = SDL_CreateRenderer(this->win, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
            throw SDLException();
        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255);
        if ((this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGB888,
                SDL_TEXTUREACCESS_TARGET, WIN_X, WIN_Y)) == NULL)
            throw SDLException();
//        this->image = (unsigned int *)malloc(sizeof(unsigned int) *
//                                            (WIN_X * WIN_Y + 1));

        cout << "INIT EVERYTHING\n";

    }
    catch (SDLException e)
    {
        cout << SDL_GetError();
    }

}

void Game::handleEvent()
{
    if (SDL_PollEvent(&(this->event)))
    {
        if (this->event.type == SDL_QUIT ||
                (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_ESCAPE))
            this->run = false;
        if (this->event.button.type == SDL_MOUSEBUTTONDOWN && this->event.button.button == SDL_BUTTON_LEFT)
        {
            this->mouseX = 0;
            this->mouseY = 0;
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
void Game::clean()
{
//    free(this->image);
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
    IMG_Quit();
    cout << "GamE OveR\n";
}

SDL_Renderer* Game::getRenderer() {
    return this->renderer;
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

