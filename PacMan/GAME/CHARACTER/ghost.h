#ifndef GHOST_H
#define GHOST_H

#include "GAME/CHARACTER/gamecharacter.h"
#include <QTimer>
#include "GAME/CHARACTER/player.h"


class Ghost : public GameCharacter
{

public:
    static bool isFeared;
protected:
    static QVector<GameCharacter *> m_players;
private:
    QVector <int> path;
    unsigned int m_mode;

public:
    Ghost(Board *map);
    ~Ghost();

    int imageState() override;

    void kill();
    void randomNextDirection();
    static void setPlayersPositions(const QVector<Player *>& players);
    void setNextMove();

    void setMode(unsigned int mode);
    GameCharacter * findClosestPlayer();
    QPoint destinyPosition();

private:
    bool hasToRecalculate();
    bool hasToRecalculate(QPoint point);
    int howManyWays();
    void generetePathToPoint(QPoint destination);




};



#endif // GHOST_H
