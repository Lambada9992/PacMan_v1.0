#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include "GAME/CHARACTER/player.h"
#include <QTcpSocket>
#include <QObject>

class OnlinePlayer :public QObject, public Player
{
    Q_OBJECT
private:
    //var
    QTcpSocket *socket;
    qintptr socketDesriptor;
    bool isConnected;
    QVector<bool> soundsToPlay;


    //methods
public:
    OnlinePlayer(QTcpSocket *socket,Board *map,SoundManager *sound,QObject *parent = nullptr);
    ~OnlinePlayer();

    virtual void soundPlayer(int i) override;

    //getery
    qintptr getSocketDescriptor();
    bool getIsConnected();


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
