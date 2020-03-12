#include "game.h"
#include <QDebug>

Game::Game()
{
    //var init
    players.resize(4);
    for(int i = 0;i<players.size();i++){
        players[i] = nullptr;
    }

    this->isLive = false;

    this->timer = new QTimer();
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTick()));


    //MyPlayer Initialization
    players[0] = new MyPlayer(&playground);
    players[0]->setPosition(playground.getSpawnPoint(0));
}

Game::~Game()
{
    //deleting players
    for(int i = 0;i<players.size();i++){
        if(players[i]!=nullptr)delete players[i];
    }

    delete timer;

}

void Game::myPlayerControl(int direction)
{
    if(!isLive)return;
    players[0]->setNextDirection(direction);

}

void Game::start()
{
    this->isLive = true;
}

void Game::stop()
{
    this->isLive = false;
}

void Game::makeMoves()
{
    for(int i =0;i<players.size();i++){
        if(players[i]!=nullptr){players[i]->move();}
    }
}

void Game::onTick()
{
    makeMoves();
    emit update();
}

