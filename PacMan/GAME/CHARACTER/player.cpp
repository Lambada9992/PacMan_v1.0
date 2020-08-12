#include "player.h"
#include <QSoundEffect>

Player::Player(Board *map,SoundManager * sound) : GameCharacter(map)
{
    this->life = 3;
    this->score = 0;
    this->m_sound = sound;


}

Player::~Player()
{

}

int Player::imageState()
{
    if(this->isAlive==false)return 4;
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

bool Player::collectBonuses()
{
    switch(this->map->collectBonus(this->position.ry(),this->position.rx())){
    case 0:
        return false;
        break;
    case 1:
        score++;
        soundPlayer(1);
        return false;
        break;
    case 2:
        soundPlayer(2);
        return true;
        break;

    }
}

void Player::kill()
{
    if(life!=0)life--;
    this->isAlive = false;
    soundPlayer(3);
}

void Player::soundPlayer(int i)
{
    if(i == 1) m_sound->playCoinCollectSound();
    if(i == 2) m_sound->playBonusCollectSound();
    if(i == 3) m_sound->playDieSound();
    if(i == 4) m_sound->playEatGhostSound();


}

void Player::setLife(unsigned int life)
{
    this->life = life;
}

void Player::setScore(unsigned int score)
{
    this->score = score;
}

unsigned int Player::getLife()
{
    return this->life;
}

unsigned int Player::getScore()
{
    return this->score;
}
