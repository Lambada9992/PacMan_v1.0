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
        players[0] = new MyPlayer(&playground);
        players[0]->setPosition(playground.getSpawnPoint(0));

        //ghosts initialization
        ghosts[0]= new Ghost(&playground);
        ghosts[0]->setPosition(playground.getSpawnPoint(4+0));
        ghosts[1]= new Ghost(&playground);
        ghosts[1]->setPosition(playground.getSpawnPoint(4+1));
        ghosts[2]= new Ghost(&playground);
        ghosts[2]->setPosition(playground.getSpawnPoint(4+2));
        ghosts[3]= new Ghost(&playground);
        ghosts[3]->setPosition(playground.getSpawnPoint(4+3));


        break;
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

}

void Game::myPlayerControl(int direction)
{
    if(!isLive)return;
    players[0]->setNextDirection(direction);

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
            players[i]->move();
            players[i]->collectBonuses();
        }
    }
    for(int i =0;i<ghosts.size();i++){
        if(ghosts[i]!=nullptr){
            ghosts[i]->randomNextDirection();
            ghosts[i]->move();
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

int Game::getTimerInterval()
{
    return this->timer->interval();
}

void Game::onTick()
{

    makeMoves();
    if(playground.ended())this->stop();
    emit update();

}

