#include "mybonus.h"
#include <QPainter>
#include <QDebug>
#include <QPen>
MyBonus::MyBonus(unsigned int x,unsigned int y,bool isBoost,unsigned int scale,QPointF boardPosition,QGraphicsItem *parent) : QGraphicsEllipseItem(parent)
{


    float sizeOfBonus;
    if(!isBoost){
        sizeOfBonus = scale/3.5;
    }else{
        sizeOfBonus = scale/2;
    }

    setRect((x*scale)+boardPosition.rx()+((scale-sizeOfBonus)/2.0),(y*scale)+boardPosition.ry()+((scale-sizeOfBonus)/2.0),sizeOfBonus,sizeOfBonus);

    QBrush brush;
    brush.setColor(QColor(255,255,100,255));
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

    setPen(Qt::NoPen);

}


