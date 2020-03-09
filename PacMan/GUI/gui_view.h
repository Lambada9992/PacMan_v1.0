#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <QGraphicsView>

#include "GAME/game.h"


class GUI_View : public QGraphicsView
{
    Q_OBJECT

    //var
private:
    QGraphicsScene *scene;
    Game game;

public:
    //konstruktor
    explicit GUI_View(QWidget *parent = nullptr);

    //display methods
    void displayMainMenu();
    void displayGame();


public slots:
    //buttons slots
    void singleplayerButtonClicked();
    //void multiplayerButtonClicked();
    void quitButtonClicked();

public:
    //keyboard
    void keyPressEvent(QKeyEvent *event);

};

#endif // GUI_VIEW_H
