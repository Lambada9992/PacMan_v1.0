#include "mainwindow.h"

#include <QApplication>
//#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication a(argc, argv);
    qDebug() << "legia";

    return a.exec();
}
