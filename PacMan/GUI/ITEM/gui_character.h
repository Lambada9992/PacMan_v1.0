#ifndef GUI_CHARACTER_H
#define GUI_CHARACTER_H

#include <QGraphicsPixmapItem>


class Gui_Character : public QGraphicsPixmapItem
{
    //VAR
    unsigned int scale;
    QPointF boardPosition;



    //METHODS
public:
    Gui_Character(QPixmap image,unsigned int scale,QPointF boardPosition,QGraphicsItem *parent = nullptr);
};

#endif // GUI_CHARACTER_H
