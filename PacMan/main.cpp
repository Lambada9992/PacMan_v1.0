#include <QApplication>
#include "GUI/gui_view.h"

/**
 *  @author Marcin Bobiński
 *  @date 21.08.2020
 *  @file main.cpp
 *  @brief Główny plik projektu
 *
 *
 * @mainpage Opis Projektu
 * PacMan jest popularną grą zręcznościową z 1980r. Poniższa dokumentacja opisuję program(grę), w którym starałem się odwzorować
 * tą popularną grę w języku C++ z wykorzystaniem Bibliotek QT.
 *
 * @section Opis Gry
 * Jest to gra 2d w której celem gracza jest zebranie jak największej ilości punktów, które zdobywa się po przez zbieranie monetek
 * oraz zjadanie przeciwnikow. Przeciwnikami są duchy, których głównym celem jest zabicie gracza
 * @section Dostępne tryby gry
 * w grze dostępne są dwa tryby gry "SinglePlayer" oraz "MultiPlayer".
 * Jak same nazwy wskazuja w trybie "SinglePlayer" gra toczy się jak w zwykłym PacManie gdzie gracz sam przeciwko duchom.
 * Tryb "MultiPlayer" w oryginalnym PacManie jednak nie występował tryb ten pozwala graczom połączyć się przez internet z innymi graczami
 * i rywalizować pomiędzy nimi.
 *
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUI_View mainwindow;
    mainwindow.show();

    return a.exec();
}
