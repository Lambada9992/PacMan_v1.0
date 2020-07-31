#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "GAME/board.h"
#include "GAME/CHARACTER/myplayer.h"
#include <QObject>
#include "GAME/CHARACTER/ghost.h"
#include <QTcpServer>
#include <QTcpSocket>
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
    int timerInterval;
    unsigned int myPlayerIndex;
    QVector<Player *> players;
    QVector<Ghost *> ghosts;
    bool isLive;
    unsigned int fearTime;
    unsigned int fearState;

    //online var HOST
    QTcpServer *server;
    QList<OnlinePlayer *> allConectedPlayers;
    //online var JOIN
    QTcpSocket *socket;
    unsigned int connectionState; //0 not connected , 1 - connecting, 2 - connected
    bool isOnlineParticipant;


    //METHODS
public://public methods
    Game();
    ~Game();

    void setMode(unsigned int mode);
    void setIsLiveAlready();
public slots:
    void start();
    void stop();
    void myPlayerControl(int direction);


public:
    GameCharacter *character(unsigned int index);
    unsigned int amountOfChracters();
    int getTimerInterval();
    QString getPlayerScoreText(unsigned const int playerIndex);
    bool getIsLive();

private:
    void makeMoves();
    void colisions();
    void clear();
    bool ended();
    bool isAnyPlayerAlive();
    void resetLevel();
    //online methods

    QString getInitStateOnline();
    void setInitStateOnline(QString initState);
    QString getStateOnline();
    void setStateOnline(QString state);
    void interpretOnlineComand(QString command);

public:
    bool getIsOnlineParticipant();
    void playerSpectatorRequest(bool status);
    void sendInitState();
    void sendStatePacket();


public slots:
    void onTick();
    void cancelFear();
    void newConnection();
    void onlinePlayerJoin(qintptr socketDescriptor);
    void onlinePlayerRemove(qintptr socketDescriptor);
    void onlinePlayerDelete(qintptr socketDescriptor);
    void connectToHost(QString ip,qint16 port = 1234);// czy napewno slot

    //join
    void readyRead();
    void disconnected();
signals:
    void messageAll(QByteArray message);
    void hostStartedGame();
    void update();
    void updateGui();//do podłączenia

};

#endif // GAME_H
