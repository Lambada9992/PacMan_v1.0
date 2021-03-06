#include "gui_character.h"
#include "Game/CHARACTER/player.h"

Gui_Character::Gui_Character(GameCharacter *character,QVector<QVector<QPixmap>> images,unsigned int scale,int timerInterval,QPointF boardPosition,QGraphicsItem *parent,QObject *pom) : QObject(pom), QGraphicsPixmapItem(parent)
{
    this->boardPosition = boardPosition;
    this->scale = scale;
    //this->extrapixel = scale/3;
    this->extrapixel = scale*(10/9.0);
    this->images = images;
    this->character = character;
    this->lastIsAliveStatus = character->getIsAlive();
    this->currentImage = 0;
    this->increaseImageIndex = true;
    this->timerInterval = timerInterval;
    this->isMoving = false;

    for(int i=0;i<this->images.size();i++){
        for(int j = 0; j < this->images[i].size();j++){
            this->images[i][j] = this->images[i][j].scaled(scale+extrapixel, scale+extrapixel, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }

    this->setPixmap(this->images[1][currentImage]);
    this->position = QPointF(boardPosition.rx()+character->getPosition().rx()*scale-(extrapixel/2),boardPosition.ry()+character->getPosition().ry()*scale-(extrapixel/2));
    this->setPos(this->position);

    if(dynamic_cast<Player*>(character)!=NULL){
        this->CollectingCoins = true;
    }else{
        this->CollectingCoins = false;
    }

    timer.setInterval((timerInterval/images[0].size())*4);
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTick()));
    timer.start();

}

Gui_Character::~Gui_Character()
{

}

void Gui_Character::updatePosition()
{

    QPointF nextPosition(boardPosition.rx()+character->getPosition().rx()*scale-(extrapixel/2),boardPosition.ry()+character->getPosition().ry()*scale-(extrapixel/2));
    if(this->pos() - nextPosition == QPointF(0,0)){
        this->isMoving = false;
    }else{
        this->isMoving = true;
    }


    setPos(nextPosition);

}

QPoint Gui_Character::getCharacterPosition()
{
    return this->character->getPosition();
}

bool Gui_Character::isCollectingCoins(){return CollectingCoins;}


void Gui_Character::onTick()
{


    if(!isMoving && (character->getIsAlive()==lastIsAliveStatus))return;
    lastIsAliveStatus = character->getIsAlive();
    int nextImageIndex = currentImage;
    if(increaseImageIndex){
        nextImageIndex = ++this->currentImage;
        if(nextImageIndex == images[character->imageState()].size()-1)
            increaseImageIndex = false;
    }else{
        nextImageIndex = --this->currentImage;
        if(nextImageIndex == 0)increaseImageIndex = true;
    }
    this->setPixmap(this->images[character->imageState()][nextImageIndex]);
    this->currentImage = nextImageIndex;

}
