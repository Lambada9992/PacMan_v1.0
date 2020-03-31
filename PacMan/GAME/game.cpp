#include "game.h"
#include <QDebug>

Game::Game()
{
    //var init
    players.resize(4);
    ghosts.resize(4);
    for(int i = 0;i<players.size();i++){
        players[i] = nullptr;
    }
    for(int i=0;i<ghosts.size();i++){
        ghosts[i] = nullptr;
    }
    this->mode = 0;
    this->timer = nullptr;
    this->isLive = false;
    this->fearTime = 5000;
    this->fearState = 0;
    this->server = nullptr;

    setMode(1);//do usuniecia


}

Game::~Game()
{
    clear();
}

void Game::setMode(unsigned int mode)
{
    clear();
    switch(mode){
    case 1:
        this->mode = 1;

        //timer Initialization
        this->timer = new QTimer();
        timer->setInterval(100);
        connect(timer,SIGNAL(timeout()),this,SLOT(onTick()));

        //MyPlayer Initialization
        myPlayerIndex = 0;
        players[0] = new MyPlayer(&playground);
        players[0]->setSpawnPosition(playground.getSpawnPoint(0));

        //ghosts initialization
        ghosts[0]= new Ghost(&playground);
        ghosts[0]->setSpawnPosition(playground.getSpawnPoint(4+0));
        ghosts[1]= new Ghost(&playground);
        ghosts[1]->setSpawnPosition(playground.getSpawnPoint(4+1));
        ghosts[2]= new Ghost(&playground);
        ghosts[2]->setSpawnPosition(playground.getSpawnPoint(4+2));
        ghosts[3]= new Ghost(&playground);
        ghosts[3]->setSpawnPosition(playground.getSpawnPoint(4+3));


        break;
    case 2:
        ////////////////////////do zmiany
        this->mode = 0;

        //timer initialization
        this->timer = new QTimer();
        timer->setInterval(100);
        connect(timer,SIGNAL(timeout()),this,SLOT(onTick()));



        server = new QTcpServer(this);
        connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
        server->listen(QHostAddress::Any,1234);

        myPlayerIndex = 0;
        players[0] = new MyPlayer(&playground);
        players[0]->setSpawnPosition(playground.getSpawnPoint(0));

    default:
        this->mode = 0;
        break;
    }
}

void Game::clear()
{
    for(int i = 0;i<players.size();i++){
        if(players[i] != nullptr){
            delete players[i];
            players[i] = nullptr;
        }
    }
    for(int i = 0;i<ghosts.size();i++){
        if(ghosts[i] != nullptr){
            delete ghosts[i];
            ghosts[i] = nullptr;
        }
    }
    if(timer!=nullptr){
        delete timer;
        timer= nullptr;
    }
    if(server!=nullptr){
        delete server;
        server = nullptr;
    }

}

bool Game::ended()
{
    if(playground.isAllBonusCollected())return true;

    for(int i =0;i<players.size();i++){
        if(players[i]!=nullptr){
            if(players[i]->getIsAlive()==true)return false;;
        }
    }

    return true;

}

void Game::myPlayerControl(int direction)
{
    if(this->mode == 0)return;
    if(!isLive)return;
    players[myPlayerIndex]->setNextDirection(direction);

}

void Game::start()
{
    if(mode==0)return;
    this->isLive = true;
    timer->start();
}

void Game::stop()
{
    if(mode==0)return;
    this->isLive = false;
    timer->stop();
}

void Game::makeMoves()
{
    for(int i =0;i<players.size();i++){
        if(players[i]!=nullptr){
            if(!players[i]->getIsAlive())continue;
            players[i]->move();
            if(players[i]->collectBonuses()){
                Ghost::isFeared=true;
                fearState++;
                QTimer::singleShot(fearTime,this,SLOT(cancelFear()));

            }
        }
    }

    this->colisions();

    for(int i =0;i<ghosts.size();i++){
        if(ghosts[i]!=nullptr){
            ghosts[i]->randomNextDirection();
            ghosts[i]->move();
        }
    }

    this->colisions();

}

void Game::colisions()
{
    for(int i =0;i<players.size();i++){

        if(players[i]==nullptr)continue;

        if(players[i]->getIsAlive()==false)continue;

        for(int j =0 ;j<ghosts.size();j++){

            if(ghosts[i]==nullptr)continue;

            if(ghosts[j]->getIsAlive()==false)continue;

            if(players[i]->getPosition()!=ghosts[j]->getPosition())continue;

            if(Ghost::isFeared == false){
                players[i]->kill();
            }else{
                ghosts[j]->kill();
            }

        }

    }

}

GameCharacter *Game::character(unsigned int index)
{
    if(index>=0 && index <players.size())return players[index];
    if(index>=players.size() && index <players.size()+ghosts.size())return ghosts[index-players.size()];//tu jak zaneguje to się nie wywala
    return nullptr;
}

unsigned int Game::amountOfChracters()
{
    return this->players.size()+this->ghosts.size();
}

bool Game::isAnyPlayerAlive()
{
    for(int i = 0;i<players.size();i++){
        if(players[i]==nullptr)continue;
        if(players[i]->getIsAlive())return true;
    }
    return false;
}

int Game::getTimerInterval()
{
    return this->timer->interval();
}

void Game::resetLevel()
{
    for(int i = 0; i<players.size();i++){
        if(players[i]==nullptr)continue;
        if(players[i]->getLife()>0){players[i]->resurect();}
    }

    for(int i = 0 ;i<ghosts.size();i++){
        if(ghosts[i]==nullptr)continue;
        ghosts[i]->goSpawn();
        ghosts[i]->resurect();
    }

    Ghost::isFeared = false;
}

void Game::onTick()
{

    makeMoves();
    emit update();

    if(playground.isAllBonusCollected()){
        this->stop();
        //go to next level
        emit update();
    }

    if(!isAnyPlayerAlive()){
        resetLevel();
        if(!isAnyPlayerAlive()){
            this->stop();
            emit update();
        }
    }



}

void Game::cancelFear()
{
    if(fearState==1){
        Ghost::isFeared = false;
        fearState--;
    }else{
        fearState--;
    }
}

void Game::newConnection()
{

}

