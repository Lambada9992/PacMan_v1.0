#include "myobstacle.h"
#include <QBrush>
#include <QDebug>
#include <QPen>


MyObstacle::MyObstacle(unsigned int x,unsigned int y,QVector<int> neighbours,unsigned int scale,QPointF boardPosition,QGraphicsItem *parent) : QGraphicsRectItem(parent)
{

    //double extraSpace = 4;
    double extraSpace = scale/double(scale-4);
    setPen(Qt::NoPen);

    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    setBrush(brush);

    setRect((x*scale)+boardPosition.x()+(neighbours[3]*scale/extraSpace),
            (y*scale)+boardPosition.y()+(neighbours[0]*scale/extraSpace),
            scale-((neighbours[1]+neighbours[3])*scale/extraSpace),
            scale-((neighbours[0]+neighbours[2])*scale/extraSpace));


}
