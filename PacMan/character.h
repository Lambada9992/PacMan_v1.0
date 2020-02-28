#ifndef CHARACTER_H
#define CHARACTER_H


class Character
{
    unsigned int y;
    unsigned int x;

    // move direction: 0-NONE, 1-Up, 2-Right, 3-Down, 4-left
    unsigned int moveDirection;
    unsigned int nextMoveDirection;
public:
    Character();
    //getery i settery
    unsigned int getY(){return this->y;}
    unsigned int getX(){return this->x;}
    unsigned int getMoveDirection(){return this->moveDirection;}
    unsigned int getNextMoveDirection(){return this->nextMoveDirection;}
};

#endif // CHARACTER_H
