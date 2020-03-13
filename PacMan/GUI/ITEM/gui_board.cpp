#include "gui_board.h"
#include <QBrush>
#include "GUI/ITEM/myobstacle.h"
#include <QDebug>


Gui_Board::Gui_Board(int x, int y, unsigned int scale,Game &game, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //position, size, theme
    this->position = QPointF(x,y);

    setRect(x,y,game.playground.getMapSizeX()*scale,game.playground.getMapSizeY()*scale);
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);


    //init var
    this->scale = scale;


    initObstacle(game);
    loadImages();
    initPlayers(game);

    //new Gui_Character(game.character(0),QPixmap(":/images/images/pacopen.png"),this->scale+5,this->position,this);

}

Gui_Board::~Gui_Board()
{
    for(int i = 0;i<this->playersAndGhosts.size();i++){
        if(playersAndGhosts[i]!= nullptr)delete playersAndGhosts[i];
    }
}

void Gui_Board::initObstacle(Game &game)
{
    this->obsctacleMap.resize(game.playground.getMapSizeY());
    for(unsigned int i = 0; i < game.playground.getMapSizeY();i++){
        this->obsctacleMap[i].resize(game.playground.getMapSizeX());
    }
    for(unsigned int i = 0;i<game.playground.getMapSizeY();i++){
        for(unsigned int j = 0; j < game.playground.getMapSizeX() ;j++){
            if(game.playground.getObstacleMap(i,j) == 0){
                this->obsctacleMap[i][j] = nullptr;
            }else{

                //1 - no neighbour , 0 - neighbour exist
                QVector<int> neighbours;
                neighbours.resize(4);

                //up
                if(i==0){neighbours[0] = 0;}else{
                    if(game.playground.getObstacleMap(i-1,j)==0){
                        neighbours[0] = 1;
                    }else{
                        neighbours[0] = 0;
                    }
                }
                //right
                if(j==game.playground.getMapSizeX()-1){neighbours[1] = 0;}else{
                    if(game.playground.getObstacleMap(i,j+1)==0){
                        neighbours[1] = 1;
                    }else{
                        neighbours[1] = 0;
                    }
                }
                //down
                if(i==game.playground.getMapSizeY()-1){neighbours[2] = 0;}else{
                    if(game.playground.getObstacleMap(i+1,j)==0){
                        neighbours[2] = 1;
                    }else{
                        neighbours[2] = 0;
                    }
                }
                //left
                if(j==0){neighbours[3] = 0;}else{
                    if(game.playground.getObstacleMap(i,j-1)==0){
                        neighbours[3] = 1;
                    }else{
                        neighbours[3] = 0;
                    }
                }

                //creating obstacle
                this->obsctacleMap[i][j] = new MyObstacle(j,i,neighbours,this->scale,this->position,this);
            }
        }
    }

}

void Gui_Board::initPlayers(Game &game)
{
    this->playersAndGhosts.resize(game.amountOfChracters());
    for(unsigned int i = 0;i < playersAndGhosts.size();i++){
        if(game.character(i)!= nullptr){
            playersAndGhosts[i] = new Gui_Character(game.character(i),images[i],this->scale,game.getTimerInterval(),this->position,this);}else{
            playersAndGhosts[i] = nullptr;
        }
    }

}

void Gui_Board::loadImages()
{
    this->images.resize(8); //4 players and 4 ghosts

    for(int i = 0 ; i<images.size()/2;i++){
        images[i].resize(5);// 4 directions + dead(empty image)
    }
    for(int i = images.size()/2 ; i<images.size();i++){
        images[i].resize(6);// 4 directions + 1 fear img + 1dead
    }

    for(int i = 0 ; i<images.size()/2;i++){
        for(int j=0;j<5;j++){
            images[i][j].resize(4);
        }
    }
    for(int i = images.size()/2 ; i<images.size();i++){
        for(int j=0;j<6;j++){
            images[i][j].resize(4);
        }
    }
    ////pac man images
    images[0] = {{QPixmap(":/images/images/paccloseu.png"),QPixmap(":/images/images/pacopen1u.png"),QPixmap(":/images/images/pacopen2u.png"),QPixmap(":/images/images/pacopen3u.png")},
                 {QPixmap(":/images/images/pacclose.png"),QPixmap(":/images/images/pacopen1.png"),QPixmap(":/images/images/pacopen2.png"),QPixmap(":/images/images/pacopen3.png")},
                 {QPixmap(":/images/images/pacclosed.png"),QPixmap(":/images/images/pacopen1d.png"),QPixmap(":/images/images/pacopen2d.png"),QPixmap(":/images/images/pacopen3d.png")},
                 {QPixmap(":/images/images/pacclosel.png"),QPixmap(":/images/images/pacopen1l.png"),QPixmap(":/images/images/pacopen2l.png"),QPixmap(":/images/images/pacopen3l.png")}


                };

}

void Gui_Board::updateCharacters()
{
    for(int i = 0;i< this->playersAndGhosts.size();i++){
        if(playersAndGhosts[i]!= nullptr)playersAndGhosts[i]->updatePosition();
    }
}
