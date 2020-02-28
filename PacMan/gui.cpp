#include "gui.h"
#include <QGraphicsTextItem>
#include "mybutton.h"


Gui::Gui(QWidget *parent) : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);
    this->setBackgroundBrush(QBrush(Qt::darkGray,Qt::SolidPattern));

    this->displayMainMenu();

}

void Gui::displayMainMenu()
{
    //clearing
    scene->clear();

    //title
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("PacMan"));
    QFont titleFont("comic sans",50);
    title->setFont(titleFont);
    int x = this->width()/2 - title->boundingRect().width()/2;
    int y = 100;
    title->setPos(x,y);
    scene->addItem(title);


    //singleplayer button
    MyButton *singleplayerButton = new MyButton(QString("Single Player"));
    x = this->width()/2 - singleplayerButton->boundingRect().width()/2;
    y = 275;
    singleplayerButton->setPos(x,y);
    connect(singleplayerButton,SIGNAL(clicked()),this,SLOT(singleplayerButtonClicked()));
    scene->addItem(singleplayerButton);

    //multiplayer button
    MyButton *multiplayerButton = new MyButton(QString("Multi Player"));
    x = this->width()/2 - multiplayerButton->boundingRect().width()/2;
    y = 350;
    multiplayerButton->setPos(x,y);
    connect(multiplayerButton,SIGNAL(clicked()),this,SLOT(multiplayerButtonClicked()));
    scene->addItem(multiplayerButton);

    //quit button
    MyButton *quitButton = new MyButton(QString("Quit"));
    x = this->width()/2 - quitButton->boundingRect().width()/2;
    y = 425;
    quitButton->setPos(x,y);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(quitButtonClicked()));
    scene->addItem(quitButton);

}

void Gui::displayGame()
{
    //clearing
    scene->clear();

}

void Gui::singleplayerButtonClicked()
{

}

void Gui::multiplayerButtonClicked()
{

}

void Gui::quitButtonClicked()
{
    exit(0);
}
