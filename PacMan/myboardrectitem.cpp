#include "myboardrectitem.h"
#include <QBrush>

MyBoardRectItem::MyBoardRectItem(int x,int y,QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(x,y,200,300);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);



}
