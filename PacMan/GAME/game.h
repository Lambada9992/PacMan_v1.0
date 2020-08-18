#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include "GAME/board.h"
#include "GAME/CHARACTER/myplayer.h"
#include <QObject>
#include "GAME/CHARACTER/ghost.h"
#include <QTcpServer>
#include <QTcpSocket>
#include "GAME/CHARACTER/onlineplayer.h"
#include "GAME/soundmanager.h"


/**
 * @brief The Game class Klasa odpowiedzialna za obsluge calej gry (czesc logiczna)
 */
class Game : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief playground zmienna klasowa przechowująca pole gry
     */
    Board playground;
private:
    unsigned int mode;
    QTimer *timer;
    int timerInterval;
    unsigned int myPlayerIndex;
    QVector<Player *> players;
    QVector<Ghost *> ghosts;
    bool isLive;
    unsigned int fearTime;
    unsigned int fearState;

    //online HOST
    QTcpServer *server;
    QList<OnlinePlayer *> allConectedPlayers;
    //online JOIN
    QTcpSocket *socket;
    unsigned int connectionState; //0 not connected , 1 - connecting, 2 - connected
    bool isOnlineParticipant;

    //Sound
    SoundManager *sound;

    //METHODS
public:
    /**
     * @brief Game konstruktor
     */
    Game();
    ~Game();

    /**
     * @brief setMode metoda pozwalajaca na wybor trybu gry
     * @param mode 0-brak, 1-sinleplayer, 2-gra wieloosobowa tryb hosta, 3-grawieloosobowa dolaczenie do hosta
     */
    void setMode(unsigned int mode);
    /**
     * @brief getMode metoda zwracajaca tryb gry
     * @return zwracany tryb gry: 0-brak, 1-sinleplayer, 2-gra wieloosobowa tryb hosta, 3-grawieloosobowa dolaczenie do hosta
     */
    unsigned int getMode();
    /**
     * @brief setIsLiveAlready metoda ktora Flaguje ze gra jest juz rozpoczeta(przydatna w przypadku rozpoczynania gry gdy chcemy aby nowi gracze nie dochodzili)
     */
    void setIsLiveAlready();
public slots:
    /**
     * @brief start start rozgrywki
     */
    void start();
    /**
     * @brief stop stop rozgrywki
     */
    void stop();
    /**
     * @brief restartGame metoda restartująca rozgrywke(zerowanie statystyk, ponowne rozstawienie)
     */
    void restartGame();
    /**
     * @brief myPlayerControl metoda do sterowania graczem
     * @param direction kierunek ruchu gracza: 1-gora, 2-prawo, 3-dol, 4-lewo
     */
    void myPlayerControl(int direction);


public:
    /**
     * @brief character metoda zwracajaca wskaznik na gracza o danym indeksie
     * @param index index
     * @return wskaznik na gracza
     */
    GameCharacter *character(unsigned int index);
    /**
     * @brief amountOfChracters zwraca maksymalna ilosc graczy+duszkow w grze
     * @return
     */
    unsigned int amountOfChracters();
    /**
     * @brief getTimerInterval Zwraca interwal czasowy glownego zegara gry
     * @return czas w ms
     */
    int getTimerInterval();
    /**
     * @brief getPlayerScoreText Zwraca wynik gracza w formie tekstowej o danym indeksie
     * @param playerIndex indeks gracza
     * @return  Wynik gracza (QString)
     */
    QString getPlayerScoreText(unsigned const int playerIndex);
    /**
     * @brief getIsLive metoda zwracajaca czy gra jest w toku
     * @return czy gra jest w toku: true - tak, false - nie
     */
    bool getIsLive();
    /**
     * @brief ended metoda zwracajaca wartosc logiczna dotyczaca konca gry
     * @return jezeli: true-gra sie zakonczyla, false-gra sie jeszcze nie zakonczyla
     */
    bool ended();

private:
    void makeMoves();
    void colisions();
    void clear();
    bool isAnyPlayerAlive();
    void resetLevel();
    void nextLevel();
    //online methods

    QString getInitStateOnline();
    void setInitStateOnline(QString initState);
    QString getStateOnline();
    void setStateOnline(QString state);
    void interpretOnlineComand(QString command);

public:
    /**
     * @brief getIsOnlineParticipant zwraca status czy jest się graczam(po podlaczeniu do hosta)
     * @return status
     */
    bool getIsOnlineParticipant();
    /**
     * @brief getConnectionState metoda zwracajaca status polaczenia
     * @return status polaczenia
     */
    int getConnectionState();
    /**
     * @brief getPLayerAmount metoda zwracająca ilosc graczy
     * @return liczba graczy
     */
    int getPLayerAmount();
    /**
     * @brief getSpectatorAmount metoda zwracająca ilosc obserwatorow gry
     * @return liczba obserwatorow
     */
    int getSpectatorAmount();
    /**
     * @brief playerSpectatorRequest metoda wysyłająca prosbe do hosta o zmiane trybu gracz/obserwujacy
     * @param status true - gracz, false - spectator
     */
    void playerSpectatorRequest(bool status);
    /**
     * @brief sendInitState metoda wysylajaca do graczy pakiet startowy
     */
    void sendInitState();
private:
    void sendStatePacket();

private slots:
    void onTick();
    void cancelFear();
    void newConnection();
    void onlinePlayerJoin(qintptr socketDescriptor);
    void onlinePlayerRemove(qintptr socketDescriptor);
    void onlinePlayerDelete(qintptr socketDescriptor);
public://dodane RESZTA BYLA PUBLIC
    /**
     * @brief connectToHost metoda pozwalajaca dolaczyc do gry po przez podanie ip hosta oraz portu
     * @param ip ip hosta
     * @param port port hosta
     */
    void connectToHost(QString ip,qint16 port = 1234);// czy napewno slot
private slots:
    //join
    void readyRead();
    void disconnected();
signals:
    void messageAll(QByteArray message);
    void hostStartedGame();
    void update();
    void updateGui();

};

#endif // GAME_H
