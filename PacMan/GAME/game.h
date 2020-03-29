#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "GAME/board.h"
#include "GAME/CHARACTER/myplayer.h"
#include <QObject>
#include "GAME/CHARACTER/ghost.h"

class Game : public QObject
{
    Q_OBJECT
    //VAR
public:
    Board playground;
private:
    unsigned int mode;
    QTimer *timer;
    QVector<Player *> players;
    QVector<Ghost *> ghosts;
    bool isLive;
    unsigned int fearTime;
    unsigned int fearState;



    //METHODS
public://public methods
    Game();
    ~Game();

    void setMode(unsigned int mode);
    void start();
    void stop();
    void myPlayerControl(int direction);


    GameCharacter *character(unsigned int index);
    unsigned int amountOfChracters();
    int getTimerInterval();
private:
    void makeMoves();
    void colisions();
    void clear();

public slots:
    void onTick();
    void cancelFear();
signals:
    void update();

};

#endif // GAME_H
