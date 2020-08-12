#ifndef PLAYER_H
#define PLAYER_H

#include "GAME/CHARACTER/gamecharacter.h"
#include "GAME/soundmanager.h"

class Player : public GameCharacter
{
    //VAR
protected:
    unsigned int life;
    unsigned int score;

    //sound manager
    SoundManager *m_sound;


    //METHODS
public:
    Player(Board *map,SoundManager *sound);
    virtual ~Player();



    int imageState() override;
    bool collectBonuses();// return true if collected fearing bonus
    void kill();
    virtual void soundPlayer(int i);// 1 - coin collect, 2 - bonus collect, 3 - die sound


    void setLife(unsigned int life);
    void setScore(unsigned int score);

    unsigned int getLife();
    unsigned int getScore();



};

#endif // PLAYER_H
