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
    static QVector<GameCharacter *> m_players;
    QVector <int> path;
    int m_pathType; // 0 - no path, 1 - destiny position path, 2 - feared path, 3 - dead path
    unsigned int m_mode;

    static bool chaseMode;
    static int chaseModeTicks;
    static int notChaseModeTicks;
public:
    Ghost(Board *map);
    ~Ghost();

    int imageState() override;

    void kill();
    static void setPlayersPositions(const QVector<Player *>& players);
    void setNextMove();

    void setMode(unsigned int mode);

private:
    void randomNextDirection();
    QPoint destinyPosition();
    GameCharacter * findClosestPlayer();
    GameCharacter * findFarestPlayer();
    QPoint randomPoint();
    bool hasToRecalculate();
    bool hasToRecalculate(QPoint point);
    int howManyWays();
    void generetePathToPoint(QPoint destination);

public:
    static void DefaultChaseModeTicks();
    static void setChaseMode(bool mode);
    static bool getChaseMode();
    static int getChaseModeTicks();
    static int getNotChaseModeTicks();
    static void nextChaseModeTicks();




};



#endif // GHOST_H
