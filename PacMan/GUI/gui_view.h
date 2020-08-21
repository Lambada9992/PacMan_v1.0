#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <QGraphicsView>
#include "GUI/ITEM/gui_board.h"
#include "GAME/game.h"
#include <QLineEdit>
#include "GUI/ITEM/mybutton.h"
#include "GAME/soundmanager.h"

/**
 * @brief The GUI_View class klasa wyswietlajaca gre(glowne okno)
 */
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
    /**
     * @brief GUI_View konstruktor
     * @param parent wskaznik na rodzica
     */
    explicit GUI_View(QWidget *parent = nullptr);
    ~GUI_View();


    //display methods
    /**
     * @brief displayMainMenu metoda wyswietlajaca menu glowne
     */
    void displayMainMenu();
    /**
     * @brief updateScoreTable metoda aktualizujaca tablice wynikow
     */
    void updateScoreTable();

public slots:
    /**
     * @brief displayGame metoda wyswietlajaca gre(pole gry,graczy, ...)
     */
    void displayGame();
    //buttons slots
    /**
     * @brief singleplayerButtonClicked metoda obslugujaca przycisk singlePlayer
     */
    void singleplayerButtonClicked();
    /**
     * @brief multiplayerButtonClicked metoda obslugujaca przycisk muliplayer
     */
    void multiplayerButtonClicked();
    /**
     * @brief quitButtonClicked metoda obslugujaca przycisk Quit
     */
    void quitButtonClicked();
    /**
     * @brief mainMenuButtonClicked metoda obslugujaca przycisk mainmenu
     */
    void mainMenuButtonClicked();
    /**
     * @brief restartButtonClicked metoda obslugujaca przycisk restart
     */
    void restartButtonClicked();

    /**
     * @brief hostButtonClicked metoda obslugujaca przycisk host
     */
    void hostButtonClicked();
    /**
     * @brief joinButtonClicked metoda obslugujaca przycisk  join
     */
    void joinButtonClicked();
    /**
     * @brief connetButtonClicked metoda obslugujaca przycisk  connect
     */
    void connetButtonClicked();
    /**
     * @brief playerSpectatorButtonClicked  metoda obslugujaca przycisk player/spectator
     */
    void playerSpectatorButtonClicked();
    /**
     * @brief startGameButtonClicked metoda obslugujaca przycisk start game
     */
    void startGameButtonClicked();
    /**
     * @brief soundButtonClicked metoda obslugujaca przycisk sound:on/off
     */
    void soundButtonClicked();


    /**
     * @brief updateGui metoda aktualizujaca wyswietlany stan rozgrywki
     */
    void updateGui();
    /**
     * @brief updateGuiItems metoda aktualizujaca wszelkiego rodzaju napisy przyciski w grze
     */
    void updateGuiItems();

    /**
     * @brief clearItems metoda sprzatajaca(powinna zostac wywolana po kazdym czyszczeniu sceny)
     */
    void clearItems();

signals:
    void directionFromKey(int);
    void updateCharacters(Game *);

};

#endif // GUI_VIEW_H
