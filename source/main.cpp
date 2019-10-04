#include "../include/Header.h"


int main(int, char**) {
    Game *game = new Game();
    game->init();
    Octopus *oct = new Octopus(game->getRenderer());

    while (game->run)
    {
        game->handleEvent();
//        oct->draw();
        SDL_RenderPresent(game->getRenderer());
    }
    game->clean();

    return 0;
}
