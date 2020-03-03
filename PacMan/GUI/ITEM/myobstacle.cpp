#include "myobstacle.h"
#include <QBrush>
#include <QDebug>


MyObstacle::MyObstacle(unsigned int x,unsigned int y,unsigned int scale,QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect((x*scale)+25,(y*scale)+25,scale,scale);
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

}
