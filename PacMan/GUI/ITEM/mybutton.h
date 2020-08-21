#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>


/**
 * @brief The MyButton class klasa odpowiedzialna za wyswietlanie oraz dzialanie przyciskow w aplikacji
 */
class MyButton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    QGraphicsTextItem *text;

public:
    /**
     * @brief MyButton Konstruktor
     * @param text tekst napisu
     * @param parent wskaznik na rodzica elementu
     */
    explicit MyButton(QString text,QGraphicsItem *parent = nullptr);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
public:
    /**
     * @brief setText metoda ustawiajaca text na napisie
     * @param text napis
     */
    void setText(QString text);

signals:
    void clicked();

};

#endif // MYBUTTON_H
