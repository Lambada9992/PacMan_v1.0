#include "onlineplayer.h"

OnlinePlayer::OnlinePlayer(QTcpSocket *socket,Board * map,SoundManager *sound,QObject *parent) : QObject(parent),Player(map,sound)
{
    this->socket = socket;
    isConnected = true;
    this->socketDesriptor = socket->socketDescriptor();
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    soundsToPlay.resize(4);
    for(int i =0 ; i< soundsToPlay.size();i++){
        soundsToPlay[i] = false;
    }
}

OnlinePlayer::~OnlinePlayer()
{
}

void OnlinePlayer::soundPlayer(int i)
{
    if(i == 1) soundsToPlay[0]=true;
    if(i == 2) soundsToPlay[1]=true;
    if(i == 3) soundsToPlay[2]=true;
    if(i == 4) soundsToPlay[3]=true;
}

void OnlinePlayer::message(QByteArray message)
{

    if(message.contains("state")){
        message.append("%S;");

        for(int i =0; i<soundsToPlay.size();i++){
            if(soundsToPlay[i]){
                message.append("1;");
                soundsToPlay[i] = false;
            }else
                message.append("0;");

        }
    }

    if(isConnected){
        socket->write(message);
        socket->waitForBytesWritten(2000);
        socket->flush();
    }
}

qintptr OnlinePlayer::getSocketDescriptor()
{
    return this->socketDesriptor;
}

bool OnlinePlayer::getIsConnected()
{
    return this->isConnected;
}

void OnlinePlayer::readyRead()
{
    isConnected =true;
    QString pom = socket->readAll();


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
    emit deletePlayer(socketDesriptor);

}
