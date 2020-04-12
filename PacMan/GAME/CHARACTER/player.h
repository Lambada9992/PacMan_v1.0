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
    virtual ~Player();

    int imageState() override;
    bool collectBonuses();// return true if collected fearing bonus
    void kill();
    void setLife(unsigned int life);

    void setScore(unsigned int score);
    unsigned int getLife();
    unsigned int getScore();



};

#endif // PLAYER_H
