#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include "GAME/CHARACTER/player.h"
#include <QTcpSocket>
#include <QObject>

class OnlinePlayer :public QObject, public Player
{
    Q_OBJECT

    //var
    QTcpSocket *socket;
    qintptr socketDesriptor;
    bool isConnected;


    //methods
public:
    OnlinePlayer(QTcpSocket *socket,Board *map,QObject *parent = nullptr);
    ~OnlinePlayer();


    //getery
    qintptr getSocketDescriptor();


public slots:
    void readyRead();
    void disconnected();
    void message(QByteArray message);

signals:
    void join(qintptr socketDescriptor);
    void remove(qintptr socketDescriptor);
    void deletePlayer(qintptr socketDescriptor);
};

#endif // ONLINEPLAYER_H
