#include "gui_board.h"
#include <QBrush>
#include "GUI/ITEM/myobstacle.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>


Gui_Board::Gui_Board(int x, int y, unsigned int scale,Game &game, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //position, size, theme
    this->position = QPointF(x,y);
    connect(this,SIGNAL(playerControl(int)),&game,SLOT(myPlayerControl(int)));

    setRect(x,y,game.playground.getMapSizeX()*scale,game.playground.getMapSizeY()*scale);
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);


    //init var
    this->scale = scale;


    initObstacle(game);
    initBonus(game);
    loadImages();
    initPlayersAndGhosts(game);

}

Gui_Board::~Gui_Board()
{
    for(int i = 0;i<this->playersAndGhosts.size();i++){
        if(playersAndGhosts[i]!= nullptr)delete playersAndGhosts[i];
    }
}

void Gui_Board::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        emit playerControl(1);
        break;
    case Qt::Key_Right:
        emit playerControl(2);
        break;
    case Qt::Key_Down:
        emit playerControl(3);
        break;
    case Qt::Key_Left:
        emit playerControl(4);
        break;
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
                if(i==0){
                    neighbours[0] = 0;
                }else{
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

void Gui_Board::initBonus(Game &game)
{
    //Vector resize
    this->bonusMap.resize(game.playground.getMapSizeY());
    for(unsigned int i = 0; i < game.playground.getMapSizeY();i++){
        this->bonusMap[i].resize(game.playground.getMapSizeX());
    }
    //filling vector(creating objects)
    for(int i = 0;i<game.playground.getMapSizeY();i++){
        for(int j = 0;j<game.playground.getMapSizeX();j++){
            switch(game.playground.getBonusMap(i,j)){
            case 1:
                this->bonusMap[i][j] = new MyBonus(j,i,false,this->scale,this->position,this);
                break;
            case 2:
                this->bonusMap[i][j] = new MyBonus(j,i,true,this->scale,this->position,this);
                break;
            default:
                this->bonusMap[i][j] = nullptr;
                break;

            }
        }
    }

}



void Gui_Board::initPlayersAndGhosts(Game &game)
{
    this->playersAndGhosts.resize(game.amountOfChracters());
    for(unsigned int i = 0;i < playersAndGhosts.size();i++){
        if(game.character(i)!= nullptr){
            playersAndGhosts[i] = new Gui_Character(game.character(i),images[i],this->scale,game.getTimerInterval(),this->position,this);
        }else{
            playersAndGhosts[i] = nullptr;
        }
    }

}

void Gui_Board::loadImages()//brakuje empty image moze znalezc sposob aby wylaczyc show()
{
    this->images.resize(8); //4 players and 4 ghosts

    for(int i = 0 ; i<images.size()/2;i++){
        images[i].resize(5);// 4 directions + dead(empty image)
    }
    for(int i = images.size()/2 ; i<images.size();i++){
        images[i].resize(6);// 4 directions + 1 fear img + 1dead
    }

    for(int i = 0 ; i<images.size()/2;i++){
        for(int j=0;j<images[i].size();j++){
            images[i][j].resize(4);
        }
    }
    for(int i = images.size()/2 ; i<images.size();i++){
        for(int j=0;j<images[i].size();j++){
            images[i][j].resize(2);
        }
    }
    ////pac man images          ///1,2,3 need new images
    images[0] = {{QPixmap(":/pacman1/images/pac0u.png"),QPixmap(":/pacman1/images/pac1u.png"),QPixmap(":/pacman1/images/pac2u.png"),QPixmap(":/pacman1/images/pac3u.png")},
                 {QPixmap(":/pacman1/images/pac0r.png"),QPixmap(":/pacman1/images/pac1r.png"),QPixmap(":/pacman1/images/pac2r.png"),QPixmap(":/pacman1/images/pac3r.png")},
                 {QPixmap(":/pacman1/images/pac0d.png"),QPixmap(":/pacman1/images/pac1d.png"),QPixmap(":/pacman1/images/pac2d.png"),QPixmap(":/pacman1/images/pac3d.png")},
                 {QPixmap(":/pacman1/images/pac0l.png"),QPixmap(":/pacman1/images/pac1l.png"),QPixmap(":/pacman1/images/pac2l.png"),QPixmap(":/pacman1/images/pac3l.png")},
                 {QPixmap(":/pacman1/images/empty.png"),QPixmap(":/pacman1/images/empty.png"),QPixmap(":/pacman1/images/empty.png"),QPixmap(":/pacman1/images/empty.png")}
                };
    images[1] = {{QPixmap(":/pacman2/images/pacgreen0u.png"),QPixmap(":/pacman2/images/pacgreen1u.png"),QPixmap(":/pacman2/images/pacgreen2u.png"),QPixmap(":/pacman2/images/pacgreen3u.png")},
                 {QPixmap(":/pacman2/images/pacgreen0r.png"),QPixmap(":/pacman2/images/pacgreen1r.png"),QPixmap(":/pacman2/images/pacgreen2r.png"),QPixmap(":/pacman2/images/pacgreen3r.png")},
                 {QPixmap(":/pacman2/images/pacgreen0d.png"),QPixmap(":/pacman2/images/pacgreen1d.png"),QPixmap(":/pacman2/images/pacgreen2d.png"),QPixmap(":/pacman2/images/pacgreen3d.png")},
                 {QPixmap(":/pacman2/images/pacgreen0l.png"),QPixmap(":/pacman2/images/pacgreen1l.png"),QPixmap(":/pacman2/images/pacgreen2l.png"),QPixmap(":/pacman2/images/pacgreen3l.png")},
                 {QPixmap(":/pacman2/images/empty.png"),QPixmap(":/pacman2/images/empty.png"),QPixmap(":/pacman2/images/empty.png"),QPixmap(":/pacman2/images/empty.png")}
                };
    images[2] = {{QPixmap(":/pacman3/images/pacpurple0u.png"),QPixmap(":/pacman3/images/pacpurple1u.png"),QPixmap(":/pacman3/images/pacpurple2u.png"),QPixmap(":/pacman3/images/pacpurple3u.png")},
                 {QPixmap(":/pacman3/images/pacpurple0r.png"),QPixmap(":/pacman3/images/pacpurple1r.png"),QPixmap(":/pacman3/images/pacpurple2r.png"),QPixmap(":/pacman3/images/pacpurple3r.png")},
                 {QPixmap(":/pacman3/images/pacpurple0d.png"),QPixmap(":/pacman3/images/pacpurple1d.png"),QPixmap(":/pacman3/images/pacpurple2d.png"),QPixmap(":/pacman3/images/pacpurple3d.png")},
                 {QPixmap(":/pacman3/images/pacpurple0l.png"),QPixmap(":/pacman3/images/pacpurple1l.png"),QPixmap(":/pacman3/images/pacpurple2l.png"),QPixmap(":/pacman3/images/pacpurple3l.png")},
                 {QPixmap(":/pacman3/images/empty.png"),QPixmap(":/pacman3/images/empty.png"),QPixmap(":/pacman3/images/empty.png"),QPixmap(":/pacman3/images/empty.png")}
                };
    images[3] = {{QPixmap(":/pacman4/images/pacbrown0u.png"),QPixmap(":/pacman4/images/pacbrown1u.png"),QPixmap(":/pacman4/images/pacbrown2u.png"),QPixmap(":/pacman4/images/pacbrown3u.png")},
                 {QPixmap(":/pacman4/images/pacbrown0r.png"),QPixmap(":/pacman4/images/pacbrown1r.png"),QPixmap(":/pacman4/images/pacbrown2r.png"),QPixmap(":/pacman4/images/pacbrown3r.png")},
                 {QPixmap(":/pacman4/images/pacbrown0d.png"),QPixmap(":/pacman4/images/pacbrown1d.png"),QPixmap(":/pacman4/images/pacbrown2d.png"),QPixmap(":/pacman4/images/pacbrown3d.png")},
                 {QPixmap(":/pacman4/images/pacbrown0l.png"),QPixmap(":/pacman4/images/pacbrown1l.png"),QPixmap(":/pacman4/images/pacbrown2l.png"),QPixmap(":/pacman4/images/pacbrown3l.png")},
                 {QPixmap(":/pacman4/images/empty.png"),QPixmap(":/pacman4/images/empty.png"),QPixmap(":/pacman4/images/empty.png"),QPixmap(":/pacman4/images/empty.png")}
                };
    images[4] = {{QPixmap(":/ghost1/images/ghostup1.png"),QPixmap(":/ghost1/images/ghostup2.png")},
                 {QPixmap(":/ghost1/images/ghostright1.png"),QPixmap(":/ghost1/images/ghostright2.png")},
                 {QPixmap(":/ghost1/images/ghostdown1.png"),QPixmap(":/ghost1/images/ghostdown2.png")},
                 {QPixmap(":/ghost1/images/ghostleft1.png"),QPixmap(":/ghost1/images/ghostleft2.png")},
                 {QPixmap(":/ghost1/images/ghostscaredblue1.png"),QPixmap(":/ghost1/images/ghostscaredblue2.png")},
                 {QPixmap(":/ghost1/images/ghostscaredwhite2.png"),QPixmap(":/ghost1/images/ghostscaredwhite2.png")}
                };
    images[5] = {{QPixmap(":/ghost2/images/ghostupblue1.png"),QPixmap(":/ghost2/images/ghostupblue2.png")},
                 {QPixmap(":/ghost2/images/ghostrightblue1.png"),QPixmap(":/ghost2/images/ghostrightblue2.png")},
                 {QPixmap(":/ghost2/images/ghostdownblue1.png"),QPixmap(":/ghost2/images/ghostdownblue2.png")},
                 {QPixmap(":/ghost2/images/ghostleftblue1.png"),QPixmap(":/ghost2/images/ghostleftblue2.png")},
                 {QPixmap(":/ghost2/images/ghostscaredblue1.png"),QPixmap(":/ghost2/images/ghostscaredblue2.png")},
                 {QPixmap(":/ghost2/images/ghostscaredwhite2.png"),QPixmap(":/ghost2/images/ghostscaredwhite2.png")}
                };
    images[6] = {{QPixmap(":/ghost3/images/ghostupred1.png"),QPixmap(":/ghost3/images/ghostupred2.png")},
                 {QPixmap(":/ghost3/images/ghostrightred1.png"),QPixmap(":/ghost3/images/ghostrightred2.png")},
                 {QPixmap(":/ghost3/images/ghostdownred1.png"),QPixmap(":/ghost3/images/ghostdownred2.png")},
                 {QPixmap(":/ghost3/images/ghostleftred1.png"),QPixmap(":/ghost3/images/ghostleftred2.png")},
                 {QPixmap(":/ghost3/images/ghostscaredblue1.png"),QPixmap(":/ghost3/images/ghostscaredblue2.png")},
                 {QPixmap(":/ghost3/images/ghostscaredwhite2.png"),QPixmap(":/ghost3/images/ghostscaredwhite2.png")}
                };
    images[7] = {{QPixmap(":/ghost4/images/ghostuporange1.png"),QPixmap(":/ghost4/images/ghostuporange2.png")},
                 {QPixmap(":/ghost4/images/ghostrightorange1.png"),QPixmap(":/ghost4/images/ghostrightorange2.png")},
                 {QPixmap(":/ghost4/images/ghostdownorange1.png"),QPixmap(":/ghost4/images/ghostdownorange2.png")},
                 {QPixmap(":/ghost4/images/ghostleftorange1.png"),QPixmap(":/ghost4/images/ghostleftorange2.png")},
                 {QPixmap(":/ghost4/images/ghostscaredblue1.png"),QPixmap(":/ghost4/images/ghostscaredblue2.png")},
                 {QPixmap(":/ghost4/images/ghostscaredwhite2.png"),QPixmap(":/ghost4/images/ghostscaredwhite2.png")}
                };

}

void Gui_Board::updateCharacters(Game *game)
{

    for(int i = 0;i< this->playersAndGhosts.size();i++){
        if(playersAndGhosts[i]!= nullptr){
            if(game->character(i)!=nullptr){
                playersAndGhosts[i]->updatePosition();
                if(playersAndGhosts[i]->isCollectingCoins()){
                    if(this->bonusMap[playersAndGhosts[i]->getCharacterPosition().ry()][playersAndGhosts[i]->getCharacterPosition().rx()]!= nullptr){
                        delete this->bonusMap[playersAndGhosts[i]->getCharacterPosition().ry()][playersAndGhosts[i]->getCharacterPosition().rx()];
                        this->bonusMap[playersAndGhosts[i]->getCharacterPosition().ry()][playersAndGhosts[i]->getCharacterPosition().rx()]=nullptr;
                    }
                }
            }

        }

    }
}

