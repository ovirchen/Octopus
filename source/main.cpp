
#include "../include/Header.h"


int main(int, char**) {
//    const int   FPS = 60;
//    const int   frameDelay = 10000 / FPS;
//    Uint32      frameStart;
//    int         frameTime;
    int count = 0;

    auto game = std::make_unique<Game>();
    game->init();

    while (game->run)
    {
        cout << count++ << endl;
//        frameStart = SDL_GetTicks();
        game->handleEvent();
        game->update();
        game->render();

//        frameTime = SDL_GetTicks() - frameStart;
//        if (frameDelay > frameTime)
//        {
//            SDL_Delay(frameDelay - frameTime);
//        }
    }
    return 0;
}
