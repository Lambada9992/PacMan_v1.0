#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <QGraphicsView>
#include "GUI/ITEM/gui_board.h"
#include "GAME/game.h"
#include <QLineEdit>


class GUI_View : public QGraphicsView
{
    Q_OBJECT

    //VAR
private:
    QGraphicsScene *scene;
    Game game;
    Gui_Board *board;
    QGraphicsTextItem *scoreTable;


    QLineEdit *lineEditBox;


    //METHODS
public://public methods
    explicit GUI_View(QWidget *parent = nullptr);
    ~GUI_View();


    //display methods
    void displayMainMenu();
    void updateScoreTable();


    //keyboard
    //void keyPressEvent(QKeyEvent *event);

public slots:
    void displayGame();
    //buttons slots
    void singleplayerButtonClicked();
    void multiplayerButtonClicked();
    void quitButtonClicked();
    void mainMenuButtonClicked();

    void hostButtonClicked();
    void joinButtonClicked();
    void connetButtonClicked();
    void playerSpectatorButtonClicked();
    void startGameButtonClicked();


    void updateGui();

signals:
    void directionFromKey(int);
    void updateCharacters(Game *);

};

#endif // GUI_VIEW_H
