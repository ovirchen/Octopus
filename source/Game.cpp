
#include "Game.h"

#define WIN_X 1920
#define WIN_Y 1080

Game::Game() {
    run = true;
    oct = std::make_unique<Octopus>();
    mouse.x = static_cast<int>(oct->getPosX());
    mouse.y = static_cast<int>(oct->getPosY());
}

Game::~Game() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    IMG_Quit();
    cout << "WINDOW CLEARED\n";
}

SDL_Renderer* Game::getRenderer() { return renderer; }

void Game::init()
{
    try {
        if ((SDL_Init(SDL_INIT_VIDEO) < 0) || (IMG_Init(IMG_INIT_PNG) < 0) ||
        (win = SDL_CreateWindow("Octopus", 0, 0, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)) == NULL)
            throw std::exception();
        if ((renderer = SDL_CreateRenderer(win, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
            throw std::exception();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        if ((texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
                SDL_TEXTUREACCESS_TARGET, WIN_X, WIN_Y)) == NULL)
            throw std::exception();
        oct->setRenderer(renderer);
        std::cout << "INIT EVERYTHING" << std::endl;
        oct->display(0, 0, 1);
    }
    catch (std::exception e)
    {
        cout << SDL_GetError() << std::endl;
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
            SDL_GetMouseState(&mouse.x, &mouse.y);
//            cout << "MOUSE " << mouse.x << " " << mouse.y << "\n";
        }
    }
}

void Game::render()
{
    oct->update(mouse);
}
