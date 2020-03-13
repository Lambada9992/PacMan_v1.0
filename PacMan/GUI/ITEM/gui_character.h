#ifndef GUI_CHARACTER_H
#define GUI_CHARACTER_H

#include <QGraphicsPixmapItem>
#include <GAME/CHARACTER/gamecharacter.h>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>
#include <QObject>


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




    //METHODS
public:
    Gui_Character(GameCharacter *character,QVector<QVector<QPixmap>> images,unsigned int scale,int timerInterval,QPointF boardPosition,QGraphicsItem *parent = nullptr,QObject *pom = nullptr);
    ~Gui_Character();
    void  updatePosition();

public slots:
    void onTick();
};

#endif // GUI_CHARACTER_H
