#ifndef MYBONUS_H
#define MYBONUS_H

#include <QGraphicsEllipseItem>

class MyBonus : public QGraphicsEllipseItem
{

private:

public:
    explicit MyBonus(unsigned int x,unsigned int y,bool isBoost,unsigned int scale,QPointF boardPosition,QGraphicsItem *parent = nullptr);

};

#endif // MYBONUS_H
