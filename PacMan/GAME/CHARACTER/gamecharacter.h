#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <QPoint>
#include "GAME/board.h"

class GameCharacter
{
    //VAR
protected:
    Board *map;
    QPoint position;
    QPoint spawnPosition;
    unsigned int direction;
    unsigned int nextDirection;
    bool isAlive;
    bool isPositioned;




    //METHODS
public:
    void resurect();
    void move();
    void goSpawn();
    virtual int imageState()=0;

    GameCharacter(Board *map);
    virtual ~GameCharacter();
    void setNextDirection(int nextDirection);
    bool setPosition(unsigned int y,unsigned int x);
    bool setPosition(QPoint position);
    bool setSpawnPosition(QPoint position);

    QPoint getPosition();
    bool getIsAlive();

};

#endif // GAMECHARACTER_H
