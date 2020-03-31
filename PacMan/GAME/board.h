#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QPoint>

class Board
{
    friend class Game;

    //VAR
private:
    unsigned int mapSizeX,mapSizeY;
    QVector<QVector<unsigned int>> obstacleMap;
    QVector<QVector<unsigned int>> bonusMap;
    unsigned int bonusLeft;
    QVector<QPoint> spawnPoints; //not implemented yet



    //METHODS
public://public methods
    Board();

    QVector<QVector<unsigned int>> getMap(){return this->obstacleMap;}

private://private methods
    void setMap(unsigned int index);
    void clearMap();
    void resizeMap(unsigned int y,unsigned int x);

public://getery i setery
    unsigned int getMapSizeY(){return mapSizeY;}
    unsigned int getMapSizeX(){return mapSizeX;}
    unsigned int getObstacleMap(unsigned int i,unsigned int j){return obstacleMap[i][j];}
    unsigned int getBonusMap(unsigned int i,unsigned int j){return bonusMap[i][j];}
    unsigned int collectBonus(unsigned int i,unsigned int j);
    QPoint getSpawnPoint(unsigned int index);
    bool isAllBonusCollected();

};

#endif // BOARD_H
