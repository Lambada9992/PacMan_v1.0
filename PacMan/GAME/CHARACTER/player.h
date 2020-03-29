#ifndef PLAYER_H
#define PLAYER_H

#include "GAME/CHARACTER/gamecharacter.h"


class Player : public GameCharacter
{
    //VAR
protected:
    unsigned int life;
    unsigned int score;


    //METHODS
public:
    Player(Board *map);

    int imageState() override;
    bool collectBonuses();// return true if collected fearing bonus



};

#endif // PLAYER_H
