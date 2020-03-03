#ifndef MYOBSTACLE_H
#define MYOBSTACLE_H

#include <QGraphicsRectItem>

class MyObstacle : public QGraphicsRectItem
{
public:
    MyObstacle(unsigned int x,unsigned int y,unsigned int scale,QGraphicsItem *parent = nullptr);
};

#endif // MYOBSTACLE_H
