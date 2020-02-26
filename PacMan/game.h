#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QList>
#include <QTcpSocket>
#include <QTimer>
#include <QObject>
#include "myserver.h"
#include "player.h"
#include "enemy.h"
#include "board.h"


class Game : public QObject
{
    Q_OBJECT

private:
    unsigned short mode; //tryby : 1-singleplayer, 2-dołączenie do hosta, 3-zostanie hostem, 4 - spectator
    QTimer *timer;
    Board board;
    QVector<Player *> players;
    QVector<Enemy *> enemies;
    QList<Player *> spectators;
    QList<Player *> queue;
    MyServer *server;
    QTcpSocket *socket;

private:
    void makeMove();

public:
    Game(QObject *parent = nullptr);
    ~Game();


    void setMode(unsigned short mode);
    void setEnemies(unsigned int ammount);

    //do usuniecia
    void printGame();

public slots:
    void onTick();


};

#endif // GAME_H
