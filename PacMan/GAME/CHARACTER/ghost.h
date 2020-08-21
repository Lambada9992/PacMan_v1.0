#ifndef GHOST_H
#define GHOST_H

#include "GAME/CHARACTER/gamecharacter.h"
#include <QTimer>
#include "GAME/CHARACTER/player.h"

/**
 * @brief The Ghost class klasa duszkow w grze dziedziczaca po GameCharacter class
 */
class Ghost : public GameCharacter
{

public:
    /**
     * @brief isFeared stan strachu duszkow
     */
    static bool isFeared;
private:
    static QVector<GameCharacter *> m_players;
    QVector <int> path;
    int m_pathType; // 0 - no path, 1 - destiny position path, 2 - feared path, 3 - dead path
    unsigned int m_mode;

    static bool chaseMode;
    static int chaseModeTicks;
    static int notChaseModeTicks;
public:
    /**
     * @brief Ghost Konstruktor
     * @param map wskaznik na mape gry
     */
    Ghost(Board *map);
    ~Ghost();

    /**
     * @brief imageState klasa zwracajaca indeks obrazka duszka do wyswietlenia
     * @return indeks obrazka
     */
    int imageState() override;

    /**
     * @brief kill metoda zabijajaca duszka(zmiana wartosci pola isAlive na false)
     */
    void kill();
    /**
     * @brief setPlayersPositions metoda przekazujaca duszka graczy(w celu wyznaczania drogi duszkow)
     * @param players
     */
    static void setPlayersPositions(const QVector<Player *>& players);
    /**
     * @brief setNextMove metoda ustalajaca nastepny ruch duszka
     */
    void setNextMove();

    /**
     * @brief setMode metoda ustalajaca tryb duszka(w jaki sposob bedzie sie poruszal po planszy)
     * @param mode tryb duszka
     */
    void setMode(unsigned int mode);

private:
    void randomNextDirection();
    QPoint destinyPosition();
    GameCharacter * findClosestPlayer();
    GameCharacter * findFarestPlayer();
    QPoint randomPoint();
    bool hasToRecalculate();
    bool hasToRecalculate(QPoint point);
    int howManyWays();
    void generetePathToPoint(QPoint destination);

public:
    /**
     * @brief DefaultChaseModeTicks metoda ustalajaca dlugosc fal atakow duszkow na wartosci poczatkowe
     */
    static void DefaultChaseModeTicks();
    /**
     * @brief setChaseMode metoda zmieniajaca tryb duszkow (domyslny tryb dla danego duszka wzgledem parametru mode/ruch do losowego pola)
     * @param mode tryb duszkow
     */
    static void setChaseMode(bool mode);
    /**
     * @brief getChaseMode metoda zwracajaca wartosc parametry ChaseMode
     * @return zwracany parametr
     */
    static bool getChaseMode();
    /**
     * @brief getChaseModeTicks metoda zwracajaca ilosc tickow sledzenia graczy
     * @return ilosc tikow
     */
    static int getChaseModeTicks();
    /**
     * @brief getNotChaseModeTicks metoda zwracajaca ilosc tikow nie sledzenia graczy(poruszanie sie do randomowo wybranego pola)
     * @return
     */
    static int getNotChaseModeTicks();
    /**
     * @brief nextChaseModeTicks zmiana wartosci tickow trybu NotChaseMode na nizsza w celu zwiekszenia poziomu trudnosci
     */
    static void nextChaseModeTicks();




};



#endif // GHOST_H
