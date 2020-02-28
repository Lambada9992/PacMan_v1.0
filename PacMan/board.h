#ifndef BOARD_H
#define BOARD_H

#include <QVector>

struct coordniatesXY{
    unsigned int x;
    unsigned int y;
};

class Board
{
private:
    unsigned int playgroundIndex;
    QVector<QVector<unsigned int>> playground;
    QVector<coordniatesXY> spawnPoints;
    QVector<int> spawnAvible;
    unsigned int playgroundSizeX;
    unsigned int playgroundSizeY;

public:
    Board();
    ~Board();

private:
    void clearPlayground();
    void resizePlayground(unsigned int y,unsigned int x);
public:
    bool isValid(unsigned int y,unsigned int x);


    //getery i setery
    unsigned int getPlaygroundIndex(){return this->playgroundIndex;}
    unsigned int getplaygroundSizeY(){return this->getplaygroundSizeY();}
    unsigned int getplaygroundSizeX(){return this->getplaygroundSizeX();}
    QVector<QVector<unsigned int>> getPlayground(){return this->playground;}

    void setMap(unsigned int index);


};

#endif // BOARD_H
