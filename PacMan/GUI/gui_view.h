#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <QGraphicsView>
#include "GUI/ITEM/gui_board.h"
#include "GAME/game.h"


class GUI_View : public QGraphicsView
{
    Q_OBJECT

    //VAR
private:
    QGraphicsScene *scene;
    Game game;
    Gui_Board *board;




    //METHODS
public://public methods
    explicit GUI_View(QWidget *parent = nullptr);
    ~GUI_View();


    //display methods
    void displayMainMenu();
    void displayGame();

    //keyboard
    void keyPressEvent(QKeyEvent *event);

public slots:
    //buttons slots
    void singleplayerButtonClicked();
    //void multiplayerButtonClicked();
    void quitButtonClicked();

    void updateGui();

signals:
    void directionFromKey(int);
    void updateCharacters();

};

#endif // GUI_VIEW_H
