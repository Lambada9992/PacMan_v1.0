#ifndef MYBOARDRECTITEM_H
#define MYBOARDRECTITEM_H

#include <QGraphicsRectItem>


class MyBoardRectItem : public QGraphicsRectItem
{
public:
    MyBoardRectItem(int x,int y,QGraphicsItem *parent = nullptr);
};

#endif // MYBOARDRECTITEM_H
