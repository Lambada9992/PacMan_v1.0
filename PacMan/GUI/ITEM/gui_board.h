#ifndef GUI_BOARD_H
#define GUI_BOARD_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPointF>
#include "GAME/game.h"



class Gui_Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    //var
private:
    QPointF position;
    QVector<QVector<QGraphicsRectItem *>> obsctacleMap;
    unsigned int scale;

public:
    explicit Gui_Board(int x,int y,unsigned int scale,Game &game, QGraphicsItem *parent = nullptr);
};

#endif // GUI_BOARD_H
