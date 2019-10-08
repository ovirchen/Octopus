
#include "Octopus.h"


Octopus::Octopus() : width{144}, height{81} {
    checkPosition(600, 500);
    mouseOct.x = static_cast<int>(pos.x);
    mouseOct.y = static_cast<int>(pos.y);
    Animation::setDestRect(width, height);
//    if (!(image = IMG_Load(R"(./Assets/img/0001.png)"))) {
//        std::cout << SDL_GetError() << std::endl;
//        std::cout << "Try again" << std::endl;
//        exit(1);
//    }
//    destRect.x = pos.x;
//    destRect.y = pos.y;
//    destRect.w = width;
//    destRect.h = height;
}
Octopus::~Octopus() {
//    SDL_FreeSurface(image);
}

//void Octopus::setRenderer(SDL_Renderer *render) { renderer = render; }
int Octopus::getPosX() { return pos.x; }
int Octopus::getPosY() { return pos.y; }

void Octopus::update(coordI mouse)
{
    if (mouseOct.x == mouse.x && mouseOct.y == mouse.y)
        return ;
    mouseOct.x = mouse.x;
    mouseOct.y = mouse.y;
    dest.x = mouse.x - width / 2;
    dest.y = mouse.y - height / 2;
    jump();
}

void Octopus::draw() {
    Animation::draw(pos);
//        SDL_RenderClear(renderer);
//        destRect.x = pos.x;
//        destRect.y = pos.y;
//        auto local_texture = SDL_CreateTextureFromSurface(renderer, image);
//        SDL_RenderCopy(renderer, local_texture, NULL, &destRect);
//        SDL_RenderPresent(renderer);
//        SDL_DestroyTexture(local_texture);
}

void Octopus::move(int i, double x, double y)
{
    int         FD = 3000;
    int         frameDelay;

    frameStart = SDL_GetTicks();
    pos.x += x;
    pos.y += y;
    draw();
    FD += 500 * i / 2;
    frameDelay = FD / FPS;
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
}

void Octopus::pushOff(double x, double y)
{
    const int   frameDelay = 15000 / FPS;
    const int   len = 3;

    int i = 0;
    x = x / len;
    y = y / len;
    while (++i <= len) {
        frameStart = SDL_GetTicks();

        changeImage(10 * i);
        pos.x += x;
        pos.y += y;
        draw();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    changeImage(40);
}

void Octopus::push(double x, double y)
{
    int         FD = 10000;
    int         frameDelay = FD / FPS;
    const int   len = 3;
    int         j = 0;

    frameStart = SDL_GetTicks();
    x = x / len;
    y = y / len;
    while (++j <= len) {
        changeImage(45 + 5 * (j % 2));
        pos.x += x;
        pos.y += y;
        draw();
    }
    changeImage(40);
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
}

void Octopus::jump()
{
    if (dest.x == pos.x && dest.y == pos.y)
        return;

    coordI      factor;
    coordD      step;
    int         i = 0;
    int         j = 2;
    double      way = sqrt(pow(dest.x - pos.x, 2) + pow(dest.y - pos.y, 2));
    findNextPush();
    int len = (way / 20) < 10 ? 10 : (way / 20);
    factor.x = 1;
    factor.y = 1;
    step.x = abs(dest.x - pos.x) / len;
    step.y = abs(dest.y - pos.y) / len;
    if (pos.x >= dest.x && pos.y >= dest.y) // 1
    {
        factor.x = -1;
        factor.y = -1;
    }
    else if (pos.x <= dest.x && pos.y > dest.y) // 2
        factor.y = -1;
    else if (pos.x > dest.x && pos.y <= dest.y) // 4
        factor.x = -1;
    step.x *= factor.x;
    step.y *= factor.y;
    pushOff(step.x, step.y);
    while(++i < (len - 1) && ((dest.x - pos.x) * factor.x) > 0 &&
            ((dest.y - pos.y) * factor.y) > 0)
    {
        if (((nextPush.x - pos.x) * factor.x) <= 0 &&
                    ((nextPush.y - pos.y) * factor.y) <= 0)
        {
            push(step.x, step.y);
            findNextPush();
            j = 1;
        }
        else
            move(j, step.x, step.y);
        ++j;
    }
    landing(step.x, step.y);
    pos.x = dest.x;
    pos.y = dest.y;
}

void Octopus::landing(double x, double y) {
    const int   frameDelay = 10000 / FPS;
    const int   len = 3;
    int         i = -1;

    x = x / len;
    y = y / len;
    while (++i < len) {
        frameStart = SDL_GetTicks();

        changeImage(45 + 5 * i);
        pos.x += x;
        pos.y += y;
        draw();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}

void Octopus::checkPosition(int map_x, int map_y) {
    pos.x = map_x - width / 2;
    pos.y = map_y - height / 2;
    dest.x = pos.x;
    dest.y = pos.y;
}

//void Octopus::changeImage(int i) {
//    std::string str;
//
//    if (i < 10) {
//        str = "./Assets/img/000" + std::to_string(i) + ".png";
//        SDL_FreeSurface(image);
//        image = IMG_Load(str.c_str());
//    }
//    else
//    {
//        str = "./Assets/img/00" + std::to_string(i) + ".png";
//        SDL_FreeSurface(image);
//        image = IMG_Load(str.c_str());
//    }
//}

void Octopus::findNextPush() {
    double t;

    t = (dest.x - pos.x) / (dest.y - pos.y);
    t = 250 / sqrt(t * t + 1);
    if (dest.y < pos.y)
        nextPush.y = pos.y - t;
    else
        nextPush.y = pos.y + t;
    nextPush.x = (nextPush.y - pos.y) * (dest.x - pos.x) / (dest.y - pos.y) + pos.x;
    cout << "NEXT STOP " << nextPush.x << " " << nextPush.y << "\n";
}
