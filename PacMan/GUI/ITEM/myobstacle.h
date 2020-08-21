#ifndef MYOBSTACLE_H
#define MYOBSTACLE_H

#include <QGraphicsRectItem>


/**
 * @brief The MyObstacle class klasa odpowiedzialna za graficzne wyswietlanie scian planszy
 */
class MyObstacle : public QGraphicsRectItem
{
public:
    /**
     * @brief MyObstacle konstruktor
     * @param x wspolrzedna pozioma
     * @param y wspolrzedna pionowa
     * @param neighbours Vector zaweirajacy informacje o wystepowaniu sasiadow elementu
     * @param scale rozmiar scianki
     * @param boardPosition pozycja pola gry
     * @param parent rodzic elementu
     */
    MyObstacle(unsigned int x,unsigned int y,QVector<int> neighbours,unsigned int scale,QPointF boardPosition,QGraphicsItem *parent = nullptr);
};

#endif // MYOBSTACLE_H
