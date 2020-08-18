#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <QGraphicsView>
#include "GUI/ITEM/gui_board.h"
#include "GAME/game.h"
#include <QLineEdit>
#include "GUI/ITEM/mybutton.h"
#include "GAME/soundmanager.h"


class GUI_View : public QGraphicsView
{
    Q_OBJECT

    //VAR
private:
    unsigned int m_scale;
    QGraphicsScene *scene;
    Game game;
    SoundManager *sound;
    Gui_Board *board;
    QGraphicsTextItem *scoreTable;
    QGraphicsTextItem *connectStatusText,*connectionModeText;
    QGraphicsTextItem *playersOnlineText,*spectatorOnlineText;
    QLineEdit *lineEditBox;
    MyButton *restartGameButton;
    MyButton *soundButton;




    //METHODS
public://public methods
    explicit GUI_View(QWidget *parent = nullptr);
    ~GUI_View();


    //display methods
    void displayMainMenu();
    void updateScoreTable();

public slots:
    void displayGame();
    //buttons slots
    void singleplayerButtonClicked();
    void multiplayerButtonClicked();
    void quitButtonClicked();
    void mainMenuButtonClicked();
    void restartButtonClicked();


    void hostButtonClicked();
    void joinButtonClicked();
    void connetButtonClicked();
    void playerSpectatorButtonClicked();
    void startGameButtonClicked();
    void soundButtonClicked();


    void updateGui();
    void updateGuiItems();

    void clearItems();

signals:
    void directionFromKey(int);
    void updateCharacters(Game *);

};

#endif // GUI_VIEW_H
