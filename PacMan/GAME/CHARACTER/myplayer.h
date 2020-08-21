#ifndef MYPLAYER_H
#define MYPLAYER_H

#include "GAME/CHARACTER/player.h"
#include <QDebug>

/**
 * @brief The MyPlayer class klasa postaci naszego gracza
 */
class MyPlayer : public Player{
    //VAR

    //METHODS
public:
    /**
     * @brief MyPlayer Konstruktor
     * @param map wskaznik na mape
     * @param sound wskaznik na interfejs dzwiekowy
     */
    MyPlayer(Board *map,SoundManager *sound);

};

#endif // MYPLAYER_H
