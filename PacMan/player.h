#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "myclient.h"


class Player : public Character
{
    unsigned int lifes;
    unsigned int score;

    qintptr socketDescriptor;
    MyClient *client;


public:
    Player();
};

#endif // PLAYER_H
