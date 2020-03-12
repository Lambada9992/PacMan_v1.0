#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <QGraphicsView>

#include "GAME/game.h"


class GUI_View : public QGraphicsView
{
    Q_OBJECT

    //VAR
private:
    QGraphicsScene *scene;
    Game game;



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

signals:
    void directionFromKey(int);

};

#endif // GUI_VIEW_H
