
#ifndef OCTOPUS_OCTOPUS_H
#define OCTOPUS_OCTOPUS_H

#include "Draw.h"
#include "Move.h"

class Octopus : public Draw, public Move {

public:
    Octopus();
    ~Octopus();

    int     getPosX();
    int     getPosY();
    void    update(coordI mouse);
    void    display(double x, double y, int i);

private:
    coordD          pos;
    coordD          dest;
    coordD          nextPush;
    coordI          mouseOct;

    void    jump();
    void    move(coordI factor, coordD step, int len);
    void    checkPosition(int map_x, int map_y);
    void    findNextPush();
};

#endif //OCTOPUS_OCTOPUS_H
