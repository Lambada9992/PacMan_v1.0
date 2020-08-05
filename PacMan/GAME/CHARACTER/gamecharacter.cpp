#include "gamecharacter.h"
#include <QDebug>

GameCharacter::GameCharacter(Board *map)
{
    //var init
    this->position.setX(0);
    this->position.setY(0);
    this->spawnPosition.setX(0);
    this->spawnPosition.setY(0);

    this->nextDirection = 0;
    this->isAlive = true;
    this->map = map;
    this->isPositioned = false;


}

GameCharacter::~GameCharacter()
{

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
    this->position.setX(position.rx());
    this->position.setY(position.ry());
    return true;
}

bool GameCharacter::setSpawnPosition(QPoint position)
{
    if(map->getMapSizeX()-1 < position.rx() || map->getMapSizeY()-1 < position.ry())return false;
    this->isPositioned = true;
    this->spawnPosition.setX(position.rx());
    this->spawnPosition.setY(position.ry());
    this->goSpawn();
    return true;
}

void GameCharacter::setIsAlive(unsigned int isAlive)
{
    this->isAlive = isAlive;
}

void GameCharacter::setDirection(unsigned int direction)
{
    this->direction = direction;
}

unsigned int GameCharacter::getDirection()
{
    return this->direction;
}

void GameCharacter::resurect()
{
    isAlive = true;
}

void GameCharacter::move()
{
    if(!this->isPositioned)return;

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
        }else{
            if(map->getObstacleMap(map->getMapSizeY()-1,position.rx())!=1){
                this->direction = this->nextDirection;
                this->setPosition(map->getMapSizeY()-1,position.rx());
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
        }else{
            if(map->getObstacleMap(position.ry(),0)!=1){
                this->direction = this->nextDirection;
                this->setPosition(position.ry(),0);
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
        }else{
            if(map->getObstacleMap(0,position.rx())!=1){
                this->direction = this->nextDirection;
                this->setPosition(0,position.rx());
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
        }else{
            if(map->getObstacleMap(position.ry(),map->getMapSizeX()-1)!=1){
                this->direction = this->nextDirection;
                this->setPosition(position.ry(),map->getMapSizeX()-1);
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

                return;
            }
        }else{
            if(map->getObstacleMap(map->getMapSizeY()-1,position.rx())!=1){
                this->setPosition(map->getMapSizeY()-1,position.rx());
                return;
            }else{

                return;
            }

        }
        break;
    case 2:
        if(this->position.rx() != map->getMapSizeX()-1){
            if(map->getObstacleMap(position.ry(),position.rx()+1)!=1){
                this->setPosition(position.ry(),position.rx()+1);
                return;
            }else{

                return;
            }
        }else{
            if(map->getObstacleMap(position.ry(),0)!=1){
                this->setPosition(position.ry(),0);
                return;
            }else{

                return;
            }

        }
        break;
    case 3:
        if(this->position.ry() != map->getMapSizeY()-1){
            if(map->getObstacleMap(position.ry()+1,position.rx())!=1){
                this->setPosition(position.ry()+1,position.rx());
                return;
            }else{

                return;
            }
        }else{
            if(map->getObstacleMap(0,position.rx())!=1){
                this->setPosition(0,position.rx());
                return;
            }else{

                return;
            }
        }
        break;
    case 4:
        if(this->position.rx() != 0){
            if(map->getObstacleMap(position.ry(),position.rx()-1)!=1){
                this->setPosition(position.ry(),position.rx()-1);
                return;
            }else{

                return;
            }
        }else{
            if(map->getObstacleMap(position.ry(),map->getMapSizeX()-1)!=1){
                this->setPosition(position.ry(),map->getMapSizeX()-1);
                return;
            }else{

                return;
            }
        }
        break;
    }


}

void GameCharacter::goSpawn()
{
 this->position=this->spawnPosition;
}

QPoint GameCharacter::getPosition()
{
    return position;
}

bool GameCharacter::getIsAlive()
{
    return this->isAlive;
}



