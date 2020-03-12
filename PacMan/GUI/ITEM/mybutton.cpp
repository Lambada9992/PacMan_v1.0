#include "mybutton.h"
#include <QBrush>
#include <QDebug>

#include <QFont>

MyButton::MyButton(QString text,QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // position, size, theme
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    this->text = new QGraphicsTextItem(text,this);

    QFont font("comic sans",15);
    this->text->setFont(font);

    int x = rect().width()/2 - this->text->boundingRect().width()/2;
    int y = rect().height()/2 - this->text->boundingRect().height()/2;
    this->text->setPos(x,y);

    setAcceptHoverEvents(true);


}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void MyButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);

}

void MyButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

}
