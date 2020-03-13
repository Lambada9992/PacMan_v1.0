#include "gui_view.h"

#include <QGraphicsSimpleTextItem>

#include "GUI/ITEM/mybutton.h"


#include <QKeyEvent>
#include <QDebug>


GUI_View::GUI_View(QWidget *parent) : QGraphicsView(parent)
{

    //window size and scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,900);

    //creating scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1024,900);
    setScene(scene);


    //display mainmenu
    this->displayMainMenu();

    connect(&this->game,SIGNAL(update()),this,SLOT(updateGui()));


}

GUI_View::~GUI_View()
{

    delete scene;
}

void GUI_View::displayMainMenu()
{
    if(scene == nullptr)return;

    //clearing
    scene->clear();

    //bg patern and color
    this->setBackgroundBrush(QBrush(Qt::darkGray,Qt::SolidPattern));

    //title "PACMAN"
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("PacMan"));
    QFont titleFont("comic sans",50,QFont::Bold);
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
    if(scene == nullptr)return;

    //clearing
    scene->clear();

    this->setBackgroundBrush(QBrush(Qt::white,Qt::SolidPattern));

    board = new Gui_Board(50,50,25,this->game);
    connect(this,SIGNAL(updateCharacters()),board,SLOT(updateCharacters()));
    scene->addItem(board);

    //game start
    game.start();
}

void GUI_View::singleplayerButtonClicked()
{
    displayGame();

}

void GUI_View::quitButtonClicked()
{
    exit(0);
}

void GUI_View::updateGui()
{
    emit updateCharacters();

}

void GUI_View::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        game.myPlayerControl(1);
        break;
    case Qt::Key_Right:
        game.myPlayerControl(2);
        break;
    case Qt::Key_Down:
        game.myPlayerControl(3);
        break;
    case Qt::Key_Left:
        game.myPlayerControl(4);
        break;
    }
}
