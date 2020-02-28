#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
private:
    unsigned int state;

public:
    Enemy();
    virtual void setNextDirection()=0;
};

#endif // ENEMY_H
