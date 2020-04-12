#include "onlineplayer.h"

OnlinePlayer::OnlinePlayer(QTcpSocket *socket,Board * map,QObject *parent) : QObject(parent),Player(map)
{
    this->socket = socket;
    isConnected = true;
    this->socketDesriptor = socket->socketDescriptor();
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

OnlinePlayer::~OnlinePlayer()
{
    socket->deleteLater();
}

void OnlinePlayer::message(QByteArray message)
{
 socket->write(message);
 socket->waitForBytesWritten(2000);
 socket->flush();
}

qintptr OnlinePlayer::getSocketDescriptor()
{
    return this->socketDesriptor;
}

void OnlinePlayer::readyRead()
{
    QString pom = socket->readAll();
    qDebug() << pom;


    if(pom == "w"){this->setNextDirection(1);return;}
    if(pom == "d"){this->setNextDirection(2);return;}
    if(pom == "s"){this->setNextDirection(3);return;}
    if(pom == "a"){this->setNextDirection(4);return;}

    if(pom == "j"){emit join(this->socketDesriptor);return;}
    if(pom == "r"){emit remove(this->socketDesriptor);return;}
    if(pom == "f"){emit deletePlayer(this->socketDesriptor);return;}

}

void OnlinePlayer::disconnected()
{
    isConnected = false;
    socket->close();
    emit deletePlayer(socketDesriptor);

}
