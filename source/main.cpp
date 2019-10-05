#include <memory>

#include "../include/Header.h"

int main(int, char**) {
    auto game = std::make_unique<Game>();
    game->init();
    auto oct = std::make_unique<Octopus>();

    while (game->run)
    {
        SDL_RenderClear(game->getRenderer());
        oct->draw(game->getRenderer());
        game->handleEvent();
    }

    return 0;
}
