#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>


class SoundManager : public QObject
{
    Q_OBJECT

public:
    enum Sounds {CoinCollect,BonusCollect,Die,EatGhost,MainMenu,Beginning,Game};

private:
    QSoundEffect m_coinCollectSound;
    QSoundEffect m_bonusCollectSound;
    QSoundEffect m_dieSound;
    QSoundEffect m_eatGhostSound;
    QSoundEffect m_beginningSound;
    QSoundEffect m_mainMenuSound;
    QSoundEffect m_gameSound;

    bool m_isMuted;

    SoundManager(QObject *parent = nullptr);

public:
    ~SoundManager();
    SoundManager (const SoundManager &) = delete ;

    static SoundManager& get();
public:
    void playCoinCollectSound();
    void playBonusCollectSound();
    void playDieSound();
    void playEatGhostSound();
    void playBeginningSound();
    void playMainMenuSound(bool var);
    void playGameSound(bool var);

    void setIsMuted(bool state);
    bool getIsMuted();
    QString getText();
public slots:
    //void soundManagerInterface(SoundManager::Sounds type,bool on=false);
    void soundManagerInterface(int type,bool on=false);

};

#endif // SOUNDMANAGER_H
