
#include "../include/Octopus.h"


Octopus::Octopus() :width{144}, height{81} {
    checkPosition(600, 500);
    mouse_x = static_cast<int>(pos_x);
    mouse_y = static_cast<int>(pos_y);
    if (!(image = IMG_Load(R"(./Assets/img/0001.png)"))) {
        std::cout << SDL_GetError() << std::endl;
        std::cout << "Try again" << std::endl;
        exit(1);
    }
    destRect.x = pos_x;
    destRect.y = pos_y;
    destRect.w = width;
    destRect.h = height;

}
Octopus::~Octopus() {
    SDL_FreeSurface(image);
}

void Octopus::setRenderer(SDL_Renderer *render) { renderer = render; }
int Octopus::getPosX() { return pos_x; }
int Octopus::getPosY() { return pos_y; }

void Octopus::update(int mouseX, int mouseY)
{
    if (mouse_x == mouseX && mouse_y == mouseY)
        return ;
    mouse_x = mouseX;
    mouse_y = mouseY;
    cout << "MOUSE " << mouseX << " " << mouseY << "\n";
    dest_x = mouseX - width / 2;
    dest_y = mouseY - height / 2;
    jump();
}

void Octopus::draw() {
//        cout << "\tdraw\n";
        SDL_RenderClear(renderer);
        destRect.x = pos_x;
        destRect.y = pos_y;
        auto local_texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, local_texture, NULL, &destRect);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(local_texture);
}

void Octopus::move(int i, double x, double y)
{
//    cout << "\tmove\n";
    int         FD = 3000;
    int         frameDelay;


    frameStart = SDL_GetTicks();
    pos_x += x;
    pos_y += y;
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
        pos_x += x;
        pos_y += y;
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
        pos_x += x;
        pos_y += y;
        draw();
    }
    changeImage(40);
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime);
}

void Octopus::jump()
{
//    cout << "\tjump\n";
    if (dest_x == pos_x && dest_y == pos_y)
        return;

    int         del_x = 1;
    int         del_y = 1;
    int         i = 0;
    int         j = 2;
    double      way = sqrt(pow(dest_x - pos_x, 2) + pow(dest_y - pos_y, 2));
    findNextPos();
    cout << "length " << way << "\n";
    int         len = way / 20;
    if (len < 10)
        len = 10;
    double      gx = abs(dest_x - pos_x) / len;
    double      gy = abs(dest_y - pos_y) / len;

    if (pos_x >= dest_x && pos_y >= dest_y) // 1
    {
        del_x = -1;
        del_y = -1;
    }
    else if (pos_x <= dest_x && pos_y > dest_y) // 2
        del_y = -1;
    else if (pos_x > dest_x && pos_y <= dest_y) // 4
        del_x = -1;

    pushOff(gx * del_x, gy * del_y);
    while(++i < (len - 1) && ((dest_x - pos_x) * del_x) > 0 &&
            ((dest_y - pos_y) * del_y) > 0)
    {
        if (((next_x - pos_x) * del_x) <= 0 && ((next_y - pos_y) * del_y) <= 0)
        {
            push(gx * del_x, gy * del_y);
            findNextPos();
            j = 1;
        }
        else
            move(j, gx * del_x, gy * del_y);
        ++j;
    }
    landing(gx * del_x, gy * del_y);

    pos_x = dest_x;
    pos_y = dest_y;
}

void Octopus::landing(double x, double y) {
//    cout << "\tlanding\n";
    const int   frameDelay = 10000 / FPS;
    const int   len = 3;
    int         i = -1;

    x = x / len;
    y = y / len;
    while (++i < len) {
        frameStart = SDL_GetTicks();

        changeImage(45 + 5 * i);
        pos_x += x;
        pos_y += y;
        draw();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}

void Octopus::checkPosition(int xMap, int yMap) {
    pos_x = xMap - width / 2;
    pos_y = yMap - height / 2;
    dest_x = pos_x;
    dest_y = pos_y;
}

void Octopus::changeImage(int i) {
    std::string str;

    if (i < 10) {
        str = "./Assets/img/000" + std::to_string(i) + ".png";
        SDL_FreeSurface(image);
        image = IMG_Load(str.c_str());
    }
    else
    {
        str = "./Assets/img/00" + std::to_string(i) + ".png";
        SDL_FreeSurface(image);
        image = IMG_Load(str.c_str());
    }
}

void Octopus::findNextPos() {
    double t;

    t = (dest_x - pos_x) / (dest_y - pos_y);
    t = 250 / sqrt(t * t + 1);
    if (dest_y < pos_y)
        next_y = pos_y - t;
    else
        next_y = pos_y + t;
    next_x = (next_y - pos_y) * (dest_x - pos_x) / (dest_y - pos_y) + pos_x;
    cout << "NEXT STOP " << next_x << " " << next_y << "\n";
}
