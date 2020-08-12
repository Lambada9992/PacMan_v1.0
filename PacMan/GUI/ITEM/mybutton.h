#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MyButton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    QGraphicsTextItem *text;

public:
    explicit MyButton(QString text,QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void setText(QString text);

signals:
    void clicked();

};

#endif // MYBUTTON_H
