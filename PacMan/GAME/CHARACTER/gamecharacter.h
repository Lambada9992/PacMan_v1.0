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
    unsigned int direction;
    unsigned int nextDirection;
    bool isAlive;
    bool isPositioned;




    //METHODS
public:
    GameCharacter(Board *map);
    void setNextDirection(int nextDirection);
    bool setPosition(unsigned int y,unsigned int x);
    bool setPosition(QPoint position);
    void move();

};

#endif // GAMECHARACTER_H
