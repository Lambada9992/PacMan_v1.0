#include "gui_board.h"
#include <QBrush>
#include "GUI/ITEM/myobstacle.h"

Gui_Board::Gui_Board(int y, int x, unsigned int sizeY, unsigned int sizeX, unsigned int scale, QVector<QVector<unsigned int> > map, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    //position, size, theme
    setRect(x,y,sizeX*scale,sizeY*scale);
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    this->setBrush(brush);



    //init var
    this->scale = scale;

    //init obstacle
    this->obsctacleMap.resize(sizeY);
    for(unsigned int i = 0; i < sizeY;i++){
        this->obsctacleMap[i].resize(sizeX);
    }
    for(unsigned int i = 0;i<sizeY;i++){
        for(unsigned int j = 0; j < sizeX ;j++){
            if(map[i][j] == 0){
                this->obsctacleMap[i][j] = nullptr;
            }else{
                this->obsctacleMap[i][j] = new MyObstacle(j,i,this->scale,this);
            }
        }
    }


}
