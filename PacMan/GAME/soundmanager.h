#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>

/**
 * @brief The SoundManager class Obsluga dzwieku w grze
 */
class SoundManager
{

private:
    QSoundEffect m_coinCollectSound;
    QSoundEffect m_bonusCollectSound;
    QSoundEffect m_dieSound;
    QSoundEffect m_eatGhostSound;
    QSoundEffect m_beginningSound;
    QSoundEffect m_mainMenuSound;
    QSoundEffect m_gameSound;

    bool m_isMuted;

    SoundManager();

public:
    ~SoundManager();
    SoundManager (const SoundManager &) = delete ;

    static SoundManager& get();
public:
    /**
     * @brief playCoinCollectSound Odtwarza dzwiek zebranej monetki
     */
    void playCoinCollectSound();
    /**
     * @brief playBonusCollectSound Odtwarza dzwiek zebranego bonusu oszałamiającego duchy
     */
    void playBonusCollectSound();
    /**
     * @brief playDieSound Odtwarza dzwiek smierci gracza
     */
    void playDieSound();
    /**
     * @brief playEatGhostSound Odtwarza dzwiek zabicia ducha przez gracza
     */
    void playEatGhostSound();
    /**
     * @brief playBeginningSound Odtwarza muzyke startu gry
     */
    void playBeginningSound();
    /**
     * @brief playMainMenuSound Odtwarza muzyke menu gry
     * @param var wlaczenie/wylaczenie muzyki
     */
    void playMainMenuSound(bool var);
    /**
     * @brief playGameSound Odtwarza muzyke w trakcie gry
     * @param var wlaczenie/wylaczenie muzyki
     */
    void playGameSound(bool var);
    /**
     * @brief setIsMuted wyciszenie wszystkich dzwiekow
     * @param state wlaczenie/wylaczenie dzwiekow
     */
    void setIsMuted(bool state);
    /**
     * @brief getIsMuted metoda odpowiedzialna za zwracanie stanu wyciszenia
     * @return stan wyciszenia
     */
    bool getIsMuted();
    /**
     * @brief getText metoda odpowiedzialna za zwracanie stanu wyciszenia w formie tekstowej
     * @return zwracany stany (QString)
     */
    QString getText();

};

#endif // SOUNDMANAGER_H
