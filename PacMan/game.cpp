#include "game.h"

void Game::makeMove(Character *item)
{
    if(item != nullptr){
        bool moveMade = 0;
        unsigned int nextMoveDirection = item->getNextMoveDirection();
        unsigned int moveDirection = item->getMoveDirection();
        int x = item->getX();
        int y = item->getY();

        if(nextMoveDirection != 0){

        }
    }

}

Game::Game(QObject *parent) : QObject(parent)
{
    this->mode = 0;
    this->timer = nullptr;
    this->player = nullptr;

    this->onlinePlayers.resize(3);
    for(int i = 0 ;i< 3;i++){
        this->onlinePlayers[i] = nullptr;
    }

    this->enemies.resize(4);
    for(int i = 0 ;i< 4;i++){
        this->enemies[i] = nullptr;
    }

    this->server = nullptr;
    this->socket = nullptr;


    window.show();

}

Game::~Game()
{

}

void Game::setMode(unsigned short mode)
{
    switch(mode){
    case 1:

        break;
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    }

}

void Game::printGame()
{
    QVector<QVector<unsigned int>> map = this->board.getPlayground();

    for(unsigned int i = 0; i < this->board.getplaygroundSizeY();i++){
        for(unsigned int j = 0 ; j< this->board.getplaygroundSizeX();j++){
            switch(map[i][j]){
            case 0:
                std::cout<<std::setw(2)<<" ";
                break;
            case 1:
                std::cout<<std::setw(2)<<"X";
                break;
            case 2:
                std::cout<<std::setw(2)<<"C";
                break;
            case 3:
                std::cout<<std::setw(2)<<"B";
                break;
            case 4:
                std::cout<<std::setw(2)<<"P";
                break;
            }
        }std::cout<<'\n';
    }

}

void Game::onTick()
{

}

