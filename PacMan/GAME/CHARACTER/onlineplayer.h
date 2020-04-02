#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include "GAME/CHARACTER/player.h"
#include <QTcpSocket>
#include <QObject>

class OnlinePlayer :public QObject, public Player
{
    Q_OBJECT

    QTcpSocket *socket;
    qintptr socketDesriptor;
    bool isConnected;
public:
    OnlinePlayer(QTcpSocket *socket,Board *map,QObject *parent = nullptr);
    ~OnlinePlayer();

    //
    qintptr getSocketDescriptor();

public slots:
    void readyRead();
    void disconnected();
};

#endif // ONLINEPLAYER_H
