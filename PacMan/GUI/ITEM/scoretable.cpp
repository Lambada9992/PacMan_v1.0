#include "scoretable.h"

ScoreTable::ScoreTable(QWidget *parent) : QTableWidget(parent)
{
    this->setRowCount(10);
    this->setColumnCount(10);
    this->setGeometry(100,100,1000000,10000000);

}
