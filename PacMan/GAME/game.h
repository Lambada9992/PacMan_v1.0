#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "GAME/board.h"
#include "GAME/CHARACTER/myplayer.h"
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
    //VAR
public:
    Board playground;
private:
    QTimer *timer;
    QVector<Player *> players;
    bool isLive;



    //METHODS
public://public methods
    Game();
    ~Game();

    void myPlayerControl(int direction);
    void start();
    void stop();
    void makeMoves();
    GameCharacter *character(unsigned int index);
    unsigned int amountOfChracters();// update when add ghosts
    int getTimerInterval();

public slots:
    void onTick();
signals:
    void update();

};

#endif // GAME_H
