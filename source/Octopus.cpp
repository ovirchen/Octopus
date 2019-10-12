
#include "Octopus.h"

Octopus::Octopus() {
    checkPosition(600, 500);
    mouseOct.x = static_cast<int>(pos.x);
    mouseOct.y = static_cast<int>(pos.y);
}
Octopus::~Octopus() {
}

int Octopus::getPosX() { return pos.x; }
int Octopus::getPosY() { return pos.y; }

void Octopus::update(coordI mouse)
{
    if (mouseOct.x == mouse.x && mouseOct.y == mouse.y)
        return ;
    mouseOct.x = mouse.x;
    mouseOct.y = mouse.y;
    dest.x = mouse.x - getWidth() / 2;
    dest.y = mouse.y - getHeight() / 2;
    jump();
}

void Octopus::move(coordI factor, coordD step, int len)
{
    int i = 0;
    int j = 2;

    findNextPush();
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
            pull(j, step.x, step.y);
        ++j;
    }
    landing(step.x, step.y);
}

void Octopus::jump()
{
    if (dest.x == pos.x && dest.y == pos.y)
        return;

    double way = sqrt(pow(dest.x - pos.x, 2) + pow(dest.y - pos.y, 2));
    int len = (way / 20) < 10 ? 10 : (way / 20);
    coordD step;
    step.x = abs(dest.x - pos.x) / len;
    step.y = abs(dest.y - pos.y) / len;
    coordI factor;
    factor.x = factor.y = 1;
    if (pos.x >= dest.x && pos.y >= dest.y) // 1
        factor.x = factor.y = -1;
    else if (pos.x <= dest.x && pos.y > dest.y) // 2
        factor.y = -1;
    else if (pos.x > dest.x && pos.y <= dest.y) // 4
        factor.x = -1;
    step.x *= factor.x;
    step.y *= factor.y;
    move(factor, step, len);
    pos.x = dest.x;
    pos.y = dest.y;
}

void Octopus::checkPosition(int map_x, int map_y) {
    pos.x = map_x - getWidth() / 2;
    pos.y = map_y - getHeight() / 2;
    dest.x = pos.x;
    dest.y = pos.y;
}

void Octopus::findNextPush() {
    double t;

    t = (dest.x - pos.x) / (dest.y - pos.y);
    t = 250 / sqrt(t * t + 1);
    if (dest.y < pos.y)
        nextPush.y = pos.y - t;
    else
        nextPush.y = pos.y + t;
    nextPush.x = (nextPush.y - pos.y) * (dest.x - pos.x) / (dest.y - pos.y) + pos.x;
}

void Octopus::display(double x, double y, int i) {
    pos.x += x;
    pos.y += y;
    changeImage(i);
    Draw::draw(pos);
}
