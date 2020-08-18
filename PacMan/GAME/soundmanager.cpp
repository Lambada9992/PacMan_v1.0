#include "soundmanager.h"


SoundManager::SoundManager() :
    m_isMuted(false)
{
    this->m_coinCollectSound.setSource(QUrl("qrc:/sounds/sounds/CoinSound.wav"));

    this->m_bonusCollectSound.setSource(QUrl("qrc:/sounds/sounds/BonusSound.wav"));
    this->m_dieSound.setSource(QUrl("qrc:/sounds/sounds/DieSound.wav"));
    this->m_eatGhostSound.setSource(QUrl("qrc:/sounds/sounds/EatGhostSound.wav"));
    this->m_beginningSound.setSource(QUrl("qrc:/sounds/sounds/BeginningSound.wav"));

    this->m_gameSound.setSource(QUrl("qrc:/sounds/sounds/GameSound.wav"));
    this->m_gameSound.setLoopCount(QSoundEffect::Infinite);

    this->m_mainMenuSound.setSource(QUrl("qrc:/sounds/sounds/MainMenuSound.wav"));
    this->m_mainMenuSound.setLoopCount(QSoundEffect::Infinite);

    this->m_coinCollectSound.setVolume(0.05);
    this->m_bonusCollectSound.setVolume(0.05);
    this->m_dieSound.setVolume(0.05);
    this->m_eatGhostSound.setVolume(0.05);
    this->m_beginningSound.setVolume(0.3);
    this->m_gameSound.setVolume(0.3);
    this->m_mainMenuSound.setVolume(0.05);
}

SoundManager::~SoundManager()
{

}

SoundManager &SoundManager::get()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::playCoinCollectSound()
{
    m_coinCollectSound.play();
}

void SoundManager::playBonusCollectSound()
{

    m_bonusCollectSound.play();
}

void SoundManager::playDieSound()
{

    m_dieSound.play();
}

void SoundManager::playEatGhostSound()
{

    m_eatGhostSound.play();
}

void SoundManager::playBeginningSound()
{

    m_beginningSound.play();
}

void SoundManager::playMainMenuSound(bool var)
{

    if(var){
        if(!m_mainMenuSound.isPlaying())
            m_mainMenuSound.play();
    }else{
        if(m_mainMenuSound.isPlaying())
            m_mainMenuSound.stop();
    }

}

void SoundManager::playGameSound(bool var)
{


    if(var){
        if(!m_gameSound.isPlaying())
            m_gameSound.play();
    }else{
        if(m_gameSound.isPlaying())
            m_gameSound.stop();
    }

}

void SoundManager::setIsMuted(bool state)
{
    m_isMuted = state;

    m_coinCollectSound.setMuted(state);
    m_bonusCollectSound.setMuted(state);
    m_eatGhostSound.setMuted(state);
    m_dieSound.setMuted(state);
    m_mainMenuSound.setMuted(state);
    m_gameSound.setMuted(state);
    m_beginningSound.setMuted(state);
}

bool SoundManager::getIsMuted()
{
    return m_isMuted;
}

QString SoundManager::getText()
{
    if(m_isMuted)
        return QString("Sound: off");
    else
        return QString("Sound: on");
}

