#include "ghost.h"
#include <QDebug>

bool Ghost::isFeared = false;

Ghost::Ghost(Board *map) : GameCharacter(map)
{

}

int Ghost::imageState()
{

    if(Ghost::isFeared==true)return 4;
    switch (this->direction) {
    case 1:
        return 0;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 2;
        break;
    case 4:
        return 3;
        break;
    default:
        return 1;
        break;
    }

}

void Ghost::randomNextDirection()
{
    this->setNextDirection(1+rand()%4);
}
