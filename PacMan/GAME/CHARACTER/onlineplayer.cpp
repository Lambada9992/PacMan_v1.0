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

}

qintptr OnlinePlayer::getSocketDescriptor()
{
    return this->socketDesriptor;
}

void OnlinePlayer::readyRead()
{
    QString pom = socket->readAll();
    qDebug() << pom;

    if(pom == "w")this->setNextDirection(1);
    if(pom == "d")this->setNextDirection(2);
    if(pom == "s")this->setNextDirection(3);
    if(pom == "a")this->setNextDirection(4);


}

void OnlinePlayer::disconnected()
{
    qDebug() << "disconnected";
    isConnected = false;
    socket->deleteLater();

}
