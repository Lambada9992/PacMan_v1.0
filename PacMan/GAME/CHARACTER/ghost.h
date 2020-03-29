#ifndef GHOST_H
#define GHOST_H

#include "GAME/CHARACTER/gamecharacter.h"
#include <QTimer>


class Ghost : public GameCharacter
{

public:
    static bool isFeared;

public:
    Ghost(Board *map);

    int imageState() override;

    void randomNextDirection();


};



#endif // GHOST_H
