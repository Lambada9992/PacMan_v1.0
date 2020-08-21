#ifndef MYBONUS_H
#define MYBONUS_H

#include <QGraphicsEllipseItem>

/**
 * @brief The MyBonus class klasa odpowiedzialna za wyswietlanie graficznie monetek oraz bonusow
 */
class MyBonus : public QGraphicsEllipseItem
{
public:
    /**
     * @brief MyBonus Konstruktor
     * @param x pozycja pozioma
     * @param y pozycja pionowa
     * @param isBoost stan logiczny: 0-monetka, 1-bonus
     * @param scale rozmiar elementu
     * @param boardPosition pozycja pola gry
     * @param parent wskaznik na rodzica
     */
    explicit MyBonus(unsigned int x,unsigned int y,bool isBoost,unsigned int scale,QPointF boardPosition,QGraphicsItem *parent = nullptr);

};

#endif // MYBONUS_H
