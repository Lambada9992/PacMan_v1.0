#ifndef GUI_CHARACTER_H
#define GUI_CHARACTER_H

#include <QGraphicsPixmapItem>
#include <GAME/CHARACTER/gamecharacter.h>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QElapsedTimer>

/**
 * @brief The Gui_Character class klasa odpowiedzialana za wyswietlanie graczy oraz duszkow
 */
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
    bool isMoving;
    bool CollectingCoins;
    bool lastIsAliveStatus;


    //METHODS
public:
    /**
     * @brief Gui_Character Konstruktor
     * @param character wskaznik na GameCharacter
     * @param images Tablica obrazow
     * @param scale rozmiar
     * @param timerInterval interwal zegara
     * @param boardPosition pozycja gry
     * @param parent wskaznik na rodzica typu QgraphicsItem
     * @param pom wskaznik na rodzica typu QObject
     */
    Gui_Character(GameCharacter *character,QVector<QVector<QPixmap>> images,unsigned int scale,int timerInterval,QPointF boardPosition,QGraphicsItem *parent = nullptr,QObject *pom = nullptr);
    ~Gui_Character();
    /**
     * @brief updatePosition metoda aktualizujaca pozycje na planszy
     */
    void  updatePosition();
    /**
     * @brief getCharacterPosition metoda zwracajaca pozycje na planszy
     * @return pozycja
     */
    QPoint getCharacterPosition();
    /**
     * @brief isCollectingCoins metoda zwracajaca wartosc logiczna czy postac zbiera monetki/bonusy z planszy
     * @return
     */
    bool isCollectingCoins();

public slots:
    /**
     * @brief onTick metoda aktualizujaca obrazek(wyswietlanego gracza duszka) jezeli sie porusza
     */
    void onTick();
};

#endif // GUI_CHARACTER_H
