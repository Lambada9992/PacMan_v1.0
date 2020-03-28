#ifndef GHOST_H
#define GHOST_H

#include "GAME/CHARACTER/gamecharacter.h"
#include <QTimer>
class Ghost : public GameCharacter
{
    static bool isFeared;
    static QTimer timer;
public:
    Ghost(Board *map);

    int imageState() override;

    void randomNextDirection();
};

#endif // GHOST_H
