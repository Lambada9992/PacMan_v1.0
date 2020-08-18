#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QPoint>
/**
 * @brief The Board class Klasa przetrzymująca plansze gry(wraz ze spawnpointami,monetkami i bonusami)
 */
class Board
{
    friend class Game;

    //VAR
private:
    unsigned int mapSizeX,mapSizeY,mapIndex;
    QVector<QVector<unsigned int>> obstacleMap;
    QVector<QVector<unsigned int>> bonusMap;
    unsigned int bonusLeft;
    QVector<QPoint> spawnPoints;



    //METHODS
public:
    Board();

private:
    void setMap(unsigned int index);
    void clearMap();
    void resizeMap(unsigned int y,unsigned int x);

public:
    /**
     * @brief getMapSizeY funkcja zwracajaca wymiar mapy w osi pionowej
     * @return Wymiar mapy w osi pionowej
     */
    unsigned int getMapSizeY();
    /**
     * @brief getMapSizeX funkcja zwracajaca wymiar mapy w osi poziomej
     * @return Wymiar mapy w osi poziomej
     */
    unsigned int getMapSizeX();
    /**
     * @brief getMapIndex Zwraca indeks aktualnej mapy
     * @return indeks aktualnej mapy
     */
    unsigned int getMapIndex();
    /**
     * @brief getObstacleMap metoda zwracajaca czy na polu o danych wspolrzednych znajduje sie sciana
     * @param i wspolrzedna Y(os pionowa)
     * @param j wspolrzedna X(os pozioma)
     * @return 0-nie sciana 1-sciana
     */
    unsigned int getObstacleMap(unsigned int i,unsigned int j);
    /**
     * @brief getBonusMap metoda zwracajaca czy na polu o danych wspolrzednych znajduje sie bonus/monetka
     * @param i wspolrzedna Y(os pionowa)
     * @param j wspolrzedna X(os pozioma)
     * @return 0-nic, 1-monetka, 2-bonus
     */
    unsigned int getBonusMap(unsigned int i,unsigned int j);
private:
    QPoint getSpawnPoint(unsigned int index);
    bool isAllBonusCollected();
public:
    /**
     * @brief collectBonus metoda zwracajaca czy na polu o danych wspolrzednych znajduje sie bonus/monetka oraz zbierajaca dany bonus z mapy
     * @param i wspolrzedna Y(os pionowa)
     * @param j wspolrzedna X(os pozioma)
     * @return 0-nic, 1-monetka, 2-bonus
     */
    unsigned int collectBonus(unsigned int i,unsigned int j);
    /**
     * @brief fixedPoint metoda zwracajaca wspolrzedne prawidlowego punnktu na mapie(jesli wyjdziemy po za zakres to zwroci punkt z 2 strony mapy)
     * @param point wspolrzedne punktu
     * @return wspolrzedne punktu prawidlowego
     */
    QPoint fixedPoint(const QPoint &point);

};

#endif // BOARD_H
