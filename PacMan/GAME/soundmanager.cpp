#include "soundmanager.h"


SoundManager::SoundManager(QObject * parent) : QObject(parent),
    m_isMuted(false)
{
    this->m_coinCollectSound.setSource(QUrl("qrc:/sounds/sounds/CoinSound.wav"));
    this->m_bonusCollectSound.setSource(QUrl("qrc:/sounds/sounds/BonusSound.wav"));
    this->m_dieSound.setSource(QUrl("qrc:/sounds/sounds/DieSound.wav"));
    this->m_eatGhostSound.setSource(QUrl("qrc:/sounds/sounds/EatGhostSound.wav"));
    this->m_beginningSound.setSource(QUrl("qrc:/sounds/sounds/BeginningSound.wav"));

    this->m_gameSound.setSource(QUrl("qrc:/sounds/sounds/GameSound.wav"));
    this->m_gameSound.setLoopCount(QSoundEffect::Infinite);

    //this->m_mainMenuSound.setSource(QUrl("qrc:/sounds/"));
    //this->m_mainMenuSound.setLoopCount(QSoundEffect::Infinite);

    //this->setIsMuted(true);
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
        //m_mainMenuSound.play();
    }else{
        //m_mainMenuSound.stop();
    }

}

void SoundManager::playGameSound(bool var)
{


    if(var){
        m_gameSound.play();
    }else{
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

//void SoundManager::soundManagerInterface(SoundManager::Sounds type, bool on)
//{
//    if(type == SoundManager::CoinCollect){
//        this->playCoinCollectSound();
//    }
//    if(type == SoundManager::BonusCollect){
//        this->playBonsuCollectSound();
//    }
//    if(type == SoundManager::Die){
//        this->playDieSound();
//    }
//    if(type == SoundManager::Beginning){
//        this->playBeginningSound();
//    }
//    if(type == SoundManager::EatGhost){
//        this->playEatGhostSound();
//    }
//    if(type == SoundManager::Game){
//        this->playGameSound(on);
//    }
//    if(type == SoundManager::MainMenu){
//        this->playMainMenuSound(on);
//    }
//}


void SoundManager::soundManagerInterface(int type, bool on)
{
    if(type == 1){

        this->playCoinCollectSound();
    }
    if(type == 2){
        this->playBonusCollectSound();
    }
    if(type == 3){
        this->playDieSound();
    }
    if(type == 4){
        this->playBeginningSound();
    }
    if(type == 5){
        this->playEatGhostSound();
    }
    if(type == 6){
        this->playGameSound(on);
    }
    if(type == 7){
        this->playMainMenuSound(on);
    }
}
