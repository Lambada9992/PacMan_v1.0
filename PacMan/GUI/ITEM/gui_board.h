#ifndef GUI_BOARD_H
#define GUI_BOARD_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QPointF>
#include "GAME/game.h"
#include "GUI/ITEM/gui_character.h"
#include "GUI/ITEM/mybonus.h"



class Gui_Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    //var
private:
    QPointF position;
    QVector<QVector<QGraphicsRectItem *>> obsctacleMap;
    QVector<QVector<QGraphicsEllipseItem *>> bonusMap;
    QVector<Gui_Character *> playersAndGhosts;
    unsigned int scale;
    QVector<QVector<QVector<QPixmap>>> images;


    //METHODS
public:
    explicit Gui_Board(int x,int y,unsigned int scale,Game &game, QGraphicsItem *parent = nullptr);
    ~Gui_Board();
    void keyPressEvent(QKeyEvent *event);

private:
    void initObstacle(Game &game);
    void initBonus(Game &game);
    void initPlayersAndGhosts(Game &game);
    void loadImages();
public slots:
    void updateCharacters(Game *);

signals:
    void  playerControl(int direction);

};

#endif // GUI_BOARD_H
