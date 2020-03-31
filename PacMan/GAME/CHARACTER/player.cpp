#include "player.h"

Player::Player(Board *map) : GameCharacter(map)
{
    this->life = 3;
    this->score = 0;


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
        return false;
        break;
    case 2:
        return true;
        break;

    }
}

void Player::kill()
{
    if(life!=0)life--;
    this->isAlive = false;
}

unsigned int Player::getLife()
{
    return this->life;
}
