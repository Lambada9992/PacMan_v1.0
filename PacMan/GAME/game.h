#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "GAME/board.h"
#include "GAME/CHARACTER/myplayer.h"
#include <QObject>
#include "GAME/CHARACTER/ghost.h"
#include <QTcpServer>
#include "GAME/CHARACTER/onlineplayer.h"

class Game : public QObject
{
    Q_OBJECT
    //VAR
public:
    Board playground;
private:
    unsigned int mode;
    QTimer *timer;
    unsigned int myPlayerIndex;
    QVector<Player *> players;
    QVector<Ghost *> ghosts;
    bool isLive;
    unsigned int fearTime;
    unsigned int fearState;

    //online var
    QTcpServer *server;
    QList<OnlinePlayer *> allConectedPlayers;



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
    bool ended();
    bool isAnyPlayerAlive();
    void resetLevel();
    //online methods
    void messageAll(std::string message);

public slots:
    void onTick();
    void cancelFear();
    void newConnection();
signals:
    void update();

};

#endif // GAME_H
