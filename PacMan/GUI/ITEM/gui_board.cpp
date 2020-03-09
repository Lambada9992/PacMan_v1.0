#include "gui_board.h"
#include <QBrush>
#include "GUI/ITEM/myobstacle.h"
#include <QDebug>

//Gui_Board::Gui_Board(int y, int x, unsigned int sizeY, unsigned int sizeX, unsigned int scale, QVector<QVector<unsigned int> > map, QGraphicsItem *parent) : QGraphicsRectItem(parent)
//{
//    //position, size, theme
//    setRect(x,y,sizeX*scale,sizeY*scale);
//    QBrush brush;
//    brush.setColor(Qt::black);
//    brush.setStyle(Qt::SolidPattern);
//    this->setBrush(brush);



//    //init var
//    this->scale = scale;

//    //init obstacle
//    this->obsctacleMap.resize(sizeY);
//    for(unsigned int i = 0; i < sizeY;i++){
//        this->obsctacleMap[i].resize(sizeX);
//    }
//    for(unsigned int i = 0;i<sizeY;i++){
//        for(unsigned int j = 0; j < sizeX ;j++){
//            if(map[i][j] == 0){
//                this->obsctacleMap[i][j] = nullptr;
//            }else{
//                this->obsctacleMap[i][j] = new MyObstacle(j,i,this->scale,this);
//            }
//        }
//    }

//}

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


    //init obstacle
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
