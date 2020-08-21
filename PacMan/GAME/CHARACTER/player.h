#ifndef PLAYER_H
#define PLAYER_H

#include "GAME/CHARACTER/gamecharacter.h"
#include "GAME/soundmanager.h"

/**
 * @brief The Player class klasa postaci gracza w grze dziedziczaca po GameCharacter
 */
class Player : public GameCharacter
{
    //VAR
protected:
    /**
     * @brief life ilosc zyc gracza
     */
    unsigned int life;
    /**
     * @brief score wynik gracza
     */
    unsigned int score;

private:
    //sound manager
    SoundManager *m_sound;

    //METHODS
public:
    /**
     * @brief Player konstruktor
     * @param map wskaznik na mape gry
     * @param sound wskaznik na interfejs dzwiekowy
     */
    Player(Board *map,SoundManager *sound);
    virtual ~Player();



    int imageState() override;
    /**
     * @brief collectBonuses metoda zbierajaca monetki/bonus na polu na ktorym aktualnie stoi gracz
     * @return true - jesli zebrano bonus, false-nie zebrano bonusu
     */
    bool collectBonuses();
    /**
     * @brief kill metoda zabijajaca gracza
     */
    void kill();
    /**
     * @brief soundPlayer metoda odtwarzajaca dzwiek o danym indeksie
     * @param i 1 - coin collect, 2 - bonus collect, 3 - die sound
     */
    virtual void soundPlayer(int i);


    /**
     * @brief setLife metoda ustawiajaca ilosc zyc gracza
     * @param life ilosc zyc
     */
    void setLife(unsigned int life);
    /**
     * @brief setScore metoda ustawiajaca ilosc punktow gracza
     * @param score ilosc punktow
     */
    void setScore(unsigned int score);
    /**
     * @brief getLife metoda zwracajaca ilosc zyc gracza
     * @return ilosc zyc
     */
    unsigned int getLife();
    /**
     * @brief getScore metoda zwracajaca ilosc punktow gracza
     * @return ilosc punktow gracza
     */
    unsigned int getScore();



};

#endif // PLAYER_H
