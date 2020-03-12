#include "gui_character.h"

Gui_Character::Gui_Character(QPixmap image,unsigned int scale,QPointF boardPosition,QGraphicsItem *parent) :  QGraphicsPixmapItem(parent)
{
    this->boardPosition = boardPosition;
    this->scale = scale;
    image = image.scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(image);

    this->setPos(QPointF(500,500));

}
