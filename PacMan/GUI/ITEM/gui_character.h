#ifndef GUI_CHARACTER_H
#define GUI_CHARACTER_H

#include <QGraphicsPixmapItem>
#include <GAME/CHARACTER/gamecharacter.h>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>
#include <QObject>
#include <QElapsedTimer>


class Gui_Character : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    //VAR
    unsigned int scale;
    float extrapixel;
    QPointF boardPosition;
    QPointF position;
    GameCharacter *character;
    QVector<QVector<QPixmap>> images;
    int currentImage;
    bool increaseImageIndex;
    int timerInterval;
    QTimer timer;
    QPropertyAnimation *animation;
    bool isMoving;
    bool CollectingCoins;

    //for animation 20.07.2020
   // QElapsedTimer animationTimer;
    //qint64 animationLastTime;



    //METHODS
public:
    Gui_Character(GameCharacter *character,QVector<QVector<QPixmap>> images,unsigned int scale,int timerInterval,QPointF boardPosition,QGraphicsItem *parent = nullptr,QObject *pom = nullptr);
    ~Gui_Character();
    void  updatePosition();
    QPoint getCharacterPosition();
    bool isCollectingCoins(){return CollectingCoins;}

public slots:
    void onTick();
};

#endif // GUI_CHARACTER_H
