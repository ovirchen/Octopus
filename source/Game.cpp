
#include "../include/Game.h"

Game::Game() {
    run = true;
    oct = std::make_unique<Octopus>();
    mouseX = static_cast<int>(oct->getPosX());
    mouseY = static_cast<int>(oct->getPosY());
}

Game::~Game() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    IMG_Quit();
    cout << "WINDOW CLEARED\n";
}

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
            SDL_GetMouseState(&mouseX, &mouseY);
            cout << "MOUSE " << mouseX << " " << mouseY << "\n";
        }
    }
}

void Game::render()
{
//    cout << "\trender\n";
    oct->update(mouseX, mouseY);
    oct->draw();

}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}
