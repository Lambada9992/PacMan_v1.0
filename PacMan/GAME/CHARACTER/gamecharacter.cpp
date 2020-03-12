#include "gamecharacter.h"

GameCharacter::GameCharacter(Board *map)
{
    //var init
    this->position.setX(0);
    this->position.setY(0);
    this->direction = 0;
    this->nextDirection = 0;
    this->isAlive = true;
    this->map = map;
    this->isPositioned = false;


}


void GameCharacter::setNextDirection(int nextDirection)
{
    switch (nextDirection) {
    case 1:
        this->nextDirection = 1;
        break;
    case 2:
        this->nextDirection = 2;
        break;
    case 3:
        this->nextDirection = 3;
        break;
    case 4:
        this->nextDirection = 4;
        break;
    default:
        this->nextDirection = 0;
        break;

    }
}

bool GameCharacter::setPosition(unsigned int y, unsigned int x)
{
    if(map->getMapSizeX()-1 < x || map->getMapSizeY()-1 < y)return false;
    this->isPositioned = true;
    this->position.setX(x);
    this->position.setY(y);
    return true;
}

bool GameCharacter::setPosition(QPoint position)
{
    if(map->getMapSizeX()-1 < position.rx() || map->getMapSizeY()-1 < position.ry())return false;
    this->isPositioned = true;
    this->position.setX(position.rx());
    this->position.setY(position.ry());
    return true;
}

void GameCharacter::move()
{
    if(this->isPositioned)return;

    switch (this->nextDirection) {
    case 0:
        break;
    case 1:
        if(this->position.ry() != 0){
            if(map->getObstacleMap(position.ry()-1,position.rx())!=1){
                this->direction = this->nextDirection;
                this->setPosition(position.ry()-1,position.rx());
                this->nextDirection = 0;
                return;
            }
        }
        break;
    case 2:
        if(this->position.rx() != map->getMapSizeX()-1){
            if(map->getObstacleMap(position.ry(),position.rx()+1)!=1){
                this->direction = this->nextDirection;
                this->setPosition(position.ry(),position.rx()+1);
                this->nextDirection = 0;
                return;
            }
        }
        break;
    case 3:
        if(this->position.ry() != map->getMapSizeY()-1){
            if(map->getObstacleMap(position.ry()+1,position.rx())!=1){
                this->direction = this->nextDirection;
                this->setPosition(position.ry()+1,position.rx());
                this->nextDirection = 0;
                return;
            }
        }
        break;
    case 4:
        if(this->position.rx() != 0){
            if(map->getObstacleMap(position.ry(),position.rx()-1)!=1){
                this->direction = this->nextDirection;
                this->setPosition(position.ry(),position.rx()-1);
                this->nextDirection = 0;
                return;
            }
        }
        break;
    }

    switch (this->direction) {
    case 0:
        break;
    case 1:
        if(this->position.ry() != 0){
            if(map->getObstacleMap(position.ry()-1,position.rx())!=1){
                this->setPosition(position.ry()-1,position.rx());
                return;
            }else{
                this->direction = 0;
            }
        }
        break;
    case 2:
        if(this->position.rx() != map->getMapSizeX()-1){
            if(map->getObstacleMap(position.ry(),position.rx()+1)!=1){
                this->setPosition(position.ry(),position.rx()+1);
                return;
            }else{
                this->direction = 0;
            }
        }
        break;
    case 3:
        if(this->position.ry() != map->getMapSizeY()-1){
            if(map->getObstacleMap(position.ry()+1,position.rx())!=1){
                this->setPosition(position.ry()+1,position.rx());
                return;
            }else{
                this->direction = 0;
            }
        }
        break;
    case 4:
        if(this->position.rx() != 0){
            if(map->getObstacleMap(position.ry(),position.rx()-1)!=1){
                this->setPosition(position.ry(),position.rx()-1);
                return;
            }else{
                this->direction = 0;
            }
        }
        break;
    }

}
