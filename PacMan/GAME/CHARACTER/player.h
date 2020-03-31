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
    ~Player();

    int imageState() override;
    bool collectBonuses();// return true if collected fearing bonus
    void kill();
    unsigned int getLife();



};

#endif // PLAYER_H
