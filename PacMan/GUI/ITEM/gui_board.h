#ifndef GUI_BOARD_H
#define GUI_BOARD_H

#include <QGraphicsRectItem>
#include <QObject>
#include "GAME/board.h"



class Gui_Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    //var
private:
    QVector<QVector<QGraphicsRectItem *>> obsctacleMap;
    unsigned int scale;

public:
    explicit Gui_Board(int y,int x,unsigned int sizeY,unsigned int sizeX,unsigned int scale,QVector<QVector<unsigned int>> map, QGraphicsItem *parent = nullptr);
};

#endif // GUI_BOARD_H
