#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <QObject>
#include <QTableWidget>

class ScoreTable :public QObject, public QTableWidget
{

public:
    ScoreTable(QWidget *parent = nullptr);
};

#endif // SCORETABLE_H
