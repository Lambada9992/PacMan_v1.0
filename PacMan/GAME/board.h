#ifndef BOARD_H
#define BOARD_H

#include <QVector>


class Board
{
    //var
    QVector<QVector<unsigned int>> map;
    unsigned int mapSizeX,mapSizeY;
    QVector<QVector<unsigned int>> bonusMap;
public:
    //konstruktor i destruktor
    Board();

    //public methods
    void setMap(unsigned int index);
    QVector<QVector<unsigned int>> getMap(){return this->map;}



private:
    //private methods
    void clearMap();
    void resizeMap(unsigned int y,unsigned int x);

    //chwilowe
public:
    unsigned int getMapSizeY(){return mapSizeY;}
    unsigned int getMapSizeX(){return mapSizeX;}
    unsigned int getObstacleMap(unsigned int i,unsigned int j){return map[i][j];}

};

#endif // BOARD_H
