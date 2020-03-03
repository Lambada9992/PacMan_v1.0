#include "gui_view.h"

#include <QGraphicsSimpleTextItem>

#include "GUI/ITEM/mybutton.h"
#include "GUI/ITEM/gui_board.h"

GUI_View::GUI_View(QWidget *parent) : QGraphicsView(parent)
{
    //window size and scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,900);

    //creating scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1024,800);
    setScene(scene);

    //bg color
    // this->setBackgroundBrush(QBrush(Qt::darkGray,Qt::SolidPattern));

    //display mainmenu
    this->displayMainMenu();

}

void GUI_View::displayMainMenu()
{
    //clearing
    if(scene == nullptr)return;

    this->setBackgroundBrush(QBrush(Qt::darkGray,Qt::SolidPattern));
    scene->clear();

    //title "PACMAN"
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
    //connect(multiplayerButton,SIGNAL(clicked()),this,SLOT(multiplayerButtonClicked()));
    scene->addItem(multiplayerButton);

    //info butonn
    MyButton *creditsButton = new MyButton(QString("Credits"));
    x = this->width()/2 - creditsButton->boundingRect().width()/2;
    y = 425;
    creditsButton->setPos(x,y);
    //connect(singleplayerButton,SIGNAL(clicked()),this,SLOT(singleplayerButtonClicked()));//////do poprawy
    scene->addItem(creditsButton);

    //quit button
    MyButton *quitButton = new MyButton(QString("Quit"));
    x = this->width()/2 - quitButton->boundingRect().width()/2;
    y = 500;
    quitButton->setPos(x,y);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(quitButtonClicked()));
    scene->addItem(quitButton);

}

void GUI_View::displayGame()
{
    //clearing
    if(scene == nullptr)return;

    this->setBackgroundBrush(QBrush(Qt::darkBlue,Qt::SolidPattern));
    scene->clear();

    Gui_Board *board = new Gui_Board(25,25,game.playground.getMapSizeY(),game.playground.getMapSizeX(),25,game.playground.getMap());
    scene->addItem(board);
}

void GUI_View::singleplayerButtonClicked()
{
    displayGame();

}

void GUI_View::quitButtonClicked()
{
    exit(0);
}
