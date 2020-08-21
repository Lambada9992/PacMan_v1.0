#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <QPoint>
#include "GAME/board.h"

/**
 * @brief The GameCharacter class kalsa Postaci w grze
 */
class GameCharacter
{

    //VAR
protected:
    /**
     * @brief map wskaznik na mape gry
     */
    Board *map;
    /**
     * @brief position aktualne polozenie postaci
     */
    QPoint position;
    /**
     * @brief spawnPosition polozenie poczatkowe postaci
     */
    QPoint spawnPosition;
    /**
     * @brief direction kierunek ruchu postaci: 0-brak, 1-gora, 2-prawo, 3-dol, 4-lewo
     */
    unsigned int direction;
    /**
     * @brief nextDirection Nastepny kierunek ruchu postaci: 0-brak, 1-gora, 2-prawo, 3-dol, 4-lewo
     */
    unsigned int nextDirection;
    /**
     * @brief isAlive Czy postac zyje
     */
    bool isAlive;
    /**
     * @brief isPositioned Czy postac zostala rozstawiona na planszy
     */
    bool isPositioned;




    //METHODS
public:

    /**
     * @brief GameCharacter Konstruktor
     * @param map wskaznik na mape gry
     */
    GameCharacter(Board *map);
    virtual ~GameCharacter();

    /**
     * @brief resurect Wskrzeszenie gracza
     */
    void resurect();
    /**
     * @brief move wykonanie ruchu przez gracza
     */
    void move();
    /**
     * @brief goSpawn Przesuniecie gracza na pozycje poczatkowa
     */
    void goSpawn();
    /**
     * @brief imageState zwrocenie indeksu zdjecia jakie ma zostac wyswietlone(w zaleznosci od kierunku zycia)
     * @return indeks zdjecia
     */
    virtual int imageState()=0;

    /**
     * @brief setNextDirection ustawienie wartosci pola nextDirection
     * @param nextDirection nastepny kierunek ruchu: 0-brak, 1-gora, 2-prawo, 3-dol, 4-lewo
     */
    void setNextDirection(int nextDirection);
    /**
     * @brief setPosition ustawienie pozycji gracza na planszy
     * @param y wspolrzedna Y (w osi pionowej)
     * @param x wspolrzedna X (w osi poziomej )
     * @return Zwraca wartosc logiczna powodzenia procesu ustawiania postaci na planszy
     */
    bool setPosition(unsigned int y,unsigned int x);
    /**
     * @brief setPosition ustawienie pozycji gracza na planszy
     * @param position wspolrzedne
     * @return Zwraca wartosc logiczna powodzenia procesu ustawiania postaci na planszy
     */
    bool setPosition(QPoint position);
    /**
     * @brief setSpawnPosition ustawienie poczatkowej pozycji gracza na planszy
     * @param position wspolrzedne
     * @return Zwraca wartosc logiczna powodzenia procesu ustawiania pozycji poczatkowej postaci na planszy
     */
    bool setSpawnPosition(QPoint position);
    /**
     * @brief setIsAlive ustawienie wartosci pola isAlive(czy postac zyje)
     * @param isAlive true-postac zyje, false- postac martwa
     */
    void setIsAlive(unsigned int isAlive);
    /**
     * @brief setDirection ustawienie wartosci pola direction(0-brak, 1-gora, 2-prawo, 3-dol, 4-lewo)
     */
    void setDirection(unsigned int);
    /**
     * @brief getDirection pobranie wartosci pola direction(0-brak, 1-gora, 2-prawo, 3-dol, 4-lewo)
     * @return kirunek ruchu
     */
    unsigned int getDirection();
    /**
     * @brief getPosition pobranie waktualnych wspolerzednych postaci
     * @return  wspolrzedne postaci
     */
    QPoint getPosition();
    /**
     * @brief getIsAlive pobranie czy dana postac zyje
     * @return isAlive true-postac zyje, false- postac martwa
     */
    bool getIsAlive();



};

#endif // GAMECHARACTER_H
