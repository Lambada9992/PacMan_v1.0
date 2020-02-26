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
    unsigned int getPlaygroundIndex(){return this->playgroundIndex;}
    void getSpawnPoint(unsigned int &y,unsigned int &x,qintptr socketDescriptor);
    void setMap(unsigned int index);
    unsigned int atIndex(unsigned int y,unsigned int x);
    unsigned int collect(unsigned int y,unsigned int x);

};

#endif // BOARD_H
