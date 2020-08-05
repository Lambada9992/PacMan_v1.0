#ifndef GHOST_H
#define GHOST_H

#include "GAME/CHARACTER/gamecharacter.h"
#include <QTimer>
#include "GAME/CHARACTER/player.h"


class Ghost : public GameCharacter
{

public:
    static bool isFeared;
private:
    QVector<QPoint> playersPositions;
    QVector <int> path;

public:
    Ghost(Board *map);
    ~Ghost();

    int imageState() override;

    void kill();
    void randomNextDirection();
    void setPlayersPositions(const QVector<Player *>& players);
    void setNextMove();

private:
    void generetePathToPoint(QPoint destination);




};



#endif // GHOST_H
