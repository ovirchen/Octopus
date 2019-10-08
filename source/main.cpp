
#include "Header.h"
#include "Game.h"


int main(int, char**) {
    auto game = std::make_unique<Game>();
    game->init();

    while (game->run)
    {
        game->handleEvent();
        game->render();
    }
    return 0;
}
