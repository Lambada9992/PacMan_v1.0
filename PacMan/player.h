#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"


class Player : public Character
{
    unsigned int life;
    unsigned int score;
    bool isAlive;



public:
    Player();
};

#endif // PLAYER_H
