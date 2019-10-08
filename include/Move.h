
#ifndef OCTOPUS_MOVE_H
#define OCTOPUS_MOVE_H

#include "Header.h"

class Move {

public:
    Move();
    ~Move();

    void            pushOff(double x, double y);
    void            pull(int i, double x, double y);
    void            push(double x, double y);
    void            landing(double x, double y);
    virtual void    display(double x, double y, int i) = 0;

private:
    Uint32          frameStart;
    int             frameTime;
    const int       FPS = 60;
};


#endif //OCTOPUS_MOVE_H
