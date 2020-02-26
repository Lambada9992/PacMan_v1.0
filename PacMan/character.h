#ifndef CHARACTER_H
#define CHARACTER_H


class Character
{
    unsigned int y;
    unsigned int x;

    unsigned int moveDirection;
    unsigned int nextMoveDirection;
public:
    Character();
    void setPossition(unsigned int y,unsigned int x);
    void getPossition(unsigned int &y,unsigned int &x);
};

#endif // CHARACTER_H
