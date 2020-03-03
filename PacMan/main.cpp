#include <QApplication>
#include "GUI/gui_view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUI_View mainwindow;
    mainwindow.show();

    return a.exec();
}
