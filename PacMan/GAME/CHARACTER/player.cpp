#include "player.h"

Player::Player(Board *map) : GameCharacter(map)
{
    this->life = 3;
    this->score = 0;


}

int Player::imageState()
{
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

void Player::collectBonuses()
{
    switch(this->map->collectBonus(this->position.ry(),this->position.rx())){
    case 0:
        return;
        break;
    case 1:
        score++;
        break;
    }
}
