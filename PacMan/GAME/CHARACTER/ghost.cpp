#include "ghost.h"
#include <QDebug>
#include "GAME/CHARACTER/mybucket.h"
#include "GAME/CHARACTER/mybucket.cpp"

//static var init
bool Ghost::isFeared = false;
QVector<GameCharacter *> Ghost::m_players;

bool Ghost::chaseMode = false;
int Ghost::chaseModeTicks = 12;
int Ghost::notChaseModeTicks = 12;

Ghost::Ghost(Board *map) : GameCharacter(map),
    m_mode(0),
    m_pathType(0)
{
    //init players position
    m_players.resize(4);
    for(int i =0;i<4;i++){
        m_players[i] = nullptr;
    }
}

Ghost::~Ghost()
{

}

void Ghost::kill()
{
    this->isAlive = false;
}

int Ghost::imageState()
{
    if(isAlive==false)return 5;
    if(Ghost::isFeared==true)return 4;
    switch (this->direction) {
    case 1:
        return 0;
        break;
    case 2:
        return 1;
        break;
    case 3:
        return 2;
        break;
    case 4:
        return 3;
        break;
    default:
        return 1;
        break;
    }

}

void Ghost::randomNextDirection()
{

    unsigned int _nextDirection = 1+rand()%4;
    if(direction==0) this->setNextDirection(_nextDirection);
    if(_nextDirection==direction)return; //setNextDirection(direction);
    if((_nextDirection+direction)%2 == 0){
        if(howManyWays()!=1)
            randomNextDirection();
        else
            this->setNextDirection(_nextDirection);
    }else{
        this->setNextDirection(_nextDirection);
    }

}

void Ghost::setPlayersPositions(const QVector<Player *>& players)
{
    for(int i = 0;i<players.size();i++){
        m_players[i] = players[i];
    }

}

void Ghost::setNextMove()
{

    if(Ghost::isFeared==false && this->position == this->spawnPosition){
        this->resurect();
    }

    if(Ghost::isFeared && this->getIsAlive()){
        // zywy i wystraszony
        if(path.size()==0 || m_pathType!=2){
            this->generetePathToPoint(randomPoint());
            if(path.size()!=0)m_pathType = 2;
        }
    }else if(this->getIsAlive()){
        //zywy nie wystraszony
        if(Ghost::getChaseMode()){
            if(path.size()==0 || m_pathType!=1){
                QPoint destiny = destinyPosition();
                if(destiny!=QPoint(-1,-1)){
                    this->generetePathToPoint(destiny);
                    if(path.size()!=0)m_pathType = 1;
                }
            }
        }else{
            if(path.size()==0 || m_pathType!=2){
                this->generetePathToPoint(randomPoint());
                if(path.size()!=0)m_pathType = 2;
            }
        }
    }else{
        //martwy
        if(path.size()==0 || m_pathType != 3){
            this->generetePathToPoint(spawnPosition);
            if(path.size()!=0)m_pathType=3;
        }
    }

    if(path.size()!=0){
        nextDirection = path[0];
        path.pop_front();
    }

}

void Ghost::setMode(unsigned int mode)
{
    m_mode = mode;
}

GameCharacter *Ghost::findClosestPlayer()
{
    GameCharacter * closestPlayer = nullptr;
    int distClosestPlayer;

    for(int i = 0 ;i<m_players.size();i++){
        if(m_players[i]){
            if(m_players[i]->getIsAlive()){
                if(closestPlayer == nullptr){
                    closestPlayer = m_players[i];
                    distClosestPlayer = (this->position.rx()-closestPlayer->getPosition().rx())*(this->position.rx()-closestPlayer->getPosition().rx());
                    distClosestPlayer += (this->position.ry()-closestPlayer->getPosition().ry())*(this->position.ry()-closestPlayer->getPosition().ry());
                }else{
                    int distCurrent = (this->position.rx()-m_players[i]->getPosition().rx())*(this->position.rx()-m_players[i]->getPosition().rx());
                    if(distCurrent < distClosestPlayer){
                        closestPlayer = m_players[i];
                        distClosestPlayer = distCurrent;
                    }
                }
            }
        }
    }
    return closestPlayer;
}

GameCharacter *Ghost::findFarestPlayer()
{
    GameCharacter * Player = nullptr;
    int distClosestPlayer;

    for(int i = 0 ;i<m_players.size();i++){
        if(m_players[i]){
            if(m_players[i]->getIsAlive()){
                if(Player == nullptr){
                    Player = m_players[i];
                    distClosestPlayer = (this->position.rx()-Player->getPosition().rx())*(this->position.rx()-Player->getPosition().rx());
                    distClosestPlayer += (this->position.ry()-Player->getPosition().ry())*(this->position.ry()-Player->getPosition().ry());
                }else{
                    int distCurrent = (this->position.rx()-m_players[i]->getPosition().rx())*(this->position.rx()-m_players[i]->getPosition().rx());
                    if(distCurrent > distClosestPlayer){
                        Player = m_players[i];
                        distClosestPlayer = distCurrent;
                    }
                }
            }
        }
    }
    return Player;
}

QPoint Ghost::randomPoint()
{
    int x,y;
    do{
        x = rand()%map->getMapSizeX();
        y = rand()%map->getMapSizeY();
    }while(map->getObstacleMap(y,x));

    QPoint result;
    result.setX(x);
    result.setY(y);

    return result;
}

QPoint Ghost::destinyPosition()
{
    if(m_mode == 0){
        GameCharacter * pom = findClosestPlayer();
        if(pom){
            return pom->getPosition();
        }else{
            return QPoint(-1,-1);
        }
    }
    if(m_mode == 1){
        GameCharacter * pom = findClosestPlayer();
        if(pom==nullptr){
            return QPoint(-1,-1);
        }else{
            if(pom->getDirection()==0){
                return pom->getPosition();
            }
            int XAdd=0,YAdd=0;
            if(pom->getDirection()==1)YAdd = -1;
            if(pom->getDirection()==2)XAdd = 1;
            if(pom->getDirection()==3)YAdd = 1;
            if(pom->getDirection()==4)XAdd = -1;


            QPoint destination = pom->getPosition();

            while(map->getObstacleMap(map->fixedPoint(destination).ry(),map->fixedPoint(destination).rx())!=1){
                destination.rx()+=XAdd;
                destination.ry()+=YAdd;

                if(destination.x()<0 || destination.x()>= map->getMapSizeX() ||destination.y()<0 || destination.y()>= map->getMapSizeY() ){
                    if(map->getObstacleMap(map->fixedPoint(destination).ry(),map->fixedPoint(destination).rx())==1){
                        destination.rx() -= XAdd;
                        destination.ry() -= YAdd;
                        return map->fixedPoint(destination);
                    }else{
                        return map->fixedPoint(destination);
                    }
                }
                if(hasToRecalculate(map->fixedPoint(destination))){

                    return map->fixedPoint(destination);
                }
            }
        }
    }
    if(m_mode == 2){
        return QPoint(-1,-1);

    }
    if(m_mode == 3){
        GameCharacter * pom = findFarestPlayer();
        if(pom){
            return pom->getPosition();
        }else{
            return QPoint(-1,-1);
        }
    }

    if(m_mode == 4){
        return randomPoint();
    }

    return QPoint(-1,-1);

}

bool Ghost::hasToRecalculate()
{
    if(this->path.size()==0)return true;

    bool isXWay = 0,isYWay =0;
    int howManyWays = 0;

    QPoint pom=position;
    pom.setX(pom.rx()-1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isXWay = true;howManyWays++;}

    pom = position;
    pom.setX(pom.rx()+1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isXWay = true;howManyWays++;}

    pom = position;
    pom.setY(pom.ry()-1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isYWay = true;howManyWays++;}

    pom = position;
    pom.setY(pom.ry()+1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isYWay = true;howManyWays++;}

    if((isXWay && isYWay) || howManyWays==1)
        return true;
    else
        return false;
}

bool Ghost::hasToRecalculate(QPoint point)
{
    bool isXWay = 0,isYWay =0;

    QPoint pom=position;
    pom.setX(pom.rx()-1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isXWay = true;}

    pom = position;
    pom.setX(pom.rx()+1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isXWay = true;}

    pom = position;
    pom.setY(pom.ry()-1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isYWay = true;}

    pom = position;
    pom.setY(pom.ry()+1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){isYWay = true;}

    if((isXWay && isYWay)|| howManyWays()==1)
        return true;
    else
        return false;
}

int Ghost::howManyWays()
{

    int howMany = 0;

    QPoint pom=position;
    pom.setX(pom.rx()-1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){howMany++;}

    pom = position;
    pom.setX(pom.rx()+1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){howMany++;}

    pom = position;
    pom.setY(pom.ry()-1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){howMany++;}

    pom = position;
    pom.setY(pom.ry()+1);
    pom = map->fixedPoint(pom);
    if(map->getObstacleMap(pom.ry(),pom.rx())!=1){howMany++;}

    return howMany;
}

struct Node{
    QPoint position;
    int g,h,f;
    QPoint parentPosition;

    void calculateH(QPoint destination){
        h = abs(position.rx()-destination.rx()) + abs(position.ry()-destination.ry());
    }
};

int positionToDirection(QPoint p1,QPoint p2){
    if(p1.rx()-p2.rx()==-1 && p1.ry()-p2.ry()==0)return 2;
    if(p1.rx()-p2.rx()==1 && p1.ry()-p2.ry()==0)return 4;
    if(p1.rx()-p2.rx()==0 && p1.ry()-p2.ry()==-1)return 3;
    if(p1.rx()-p2.rx()==0 && p1.ry()-p2.ry()==1)return 1;

    return 0;
}


void Ghost::generetePathToPoint(QPoint destination)
{

    bool found = false;
    Node last;


    QVector<QVector <bool>> visitMap;
    visitMap.resize(map->getMapSizeY());
    for(int i = 0 ; i< map->getMapSizeY();i++){
        visitMap[i].resize(map->getMapSizeX());
        for(int j = 0;j<map->getMapSizeX();j++){
            visitMap[i][j] = false;
        }
    }

    QVector<QVector <QPoint>> parentMap;
    parentMap.resize(map->getMapSizeY());
    for(int i = 0 ; i< map->getMapSizeY();i++){
        parentMap[i].resize(map->getMapSizeX());
        for(int j = 0;j<map->getMapSizeX();j++){
            parentMap[i][j] =QPoint(-1,-1) ;
        }
    }

    MyBucket<Node> openSet;

    Node initNode;
    initNode.g = 0;
    initNode.position = this->position;
    initNode.parentPosition = QPoint(-1,-1);
    initNode.calculateH(destination);
    initNode.f = initNode.g + initNode.h;
    openSet.push(initNode,initNode.f);
    int i =1;
    while(openSet.getSize()!=0){//get size moze zwracac wyjatek const char *
        Node pom = openSet.pop();

        if(pom.position == destination){
            found = true;
            last = pom;
            parentMap[pom.position.ry()][pom.position.rx()] = pom.parentPosition;
            break; //reconstruct path
        }


        visitMap[pom.position.ry()][pom.position.rx()] = true;
        parentMap[pom.position.ry()][pom.position.rx()] = pom.parentPosition;

        //dzieci
        int x,y;
        ////d1
        x = pom.position.rx()-1;
        y = pom.position.ry();
        if(x==-1){x = map->getMapSizeX()-1;}
        if(x==map->getMapSizeX()){x = 0;}
        if(y==-1){y = map->getMapSizeY()-1;}
        if(y==map->getMapSizeY()){y = 0;}
        if(map->getObstacleMap(y,x)==0){
            if(visitMap[y][x]==false){
                Node dziecko;
                dziecko.parentPosition = pom.position;
                dziecko.g = pom.g+1;
                dziecko.calculateH(destination);
                dziecko.f = dziecko.g+dziecko.h;
                dziecko.position = QPoint(x,y);
                openSet.push(dziecko,dziecko.f);
            }
        }
        ////d2
        x = pom.position.rx()+1;
        y = pom.position.ry();
        if(x==-1){x = map->getMapSizeX()-1;}
        if(x==map->getMapSizeX()){x = 0;}
        if(y==-1){y = map->getMapSizeY()-1;}
        if(y==map->getMapSizeY()){y = 0;}
        if(map->getObstacleMap(y,x)==0){
            if(visitMap[y][x]==false){
                Node dziecko;
                dziecko.parentPosition = pom.position;
                dziecko.g = pom.g+1;
                dziecko.calculateH(destination);
                dziecko.f = dziecko.g+dziecko.h;
                dziecko.position = QPoint(x,y);
                openSet.push(dziecko,dziecko.f);
            }
        }
        ////d3
        x = pom.position.rx();
        y = pom.position.ry()-1;
        if(x==-1){x = map->getMapSizeX()-1;}
        if(x==map->getMapSizeX()){x = 0;}
        if(y==-1){y = map->getMapSizeY()-1;}
        if(y==map->getMapSizeY()){y = 0;}
        if(map->getObstacleMap(y,x)==0){
            if(visitMap[y][x]==false){
                Node dziecko;
                dziecko.parentPosition = pom.position;
                dziecko.g = pom.g+1;
                dziecko.calculateH(destination);
                dziecko.f = dziecko.g+dziecko.h;
                dziecko.position = QPoint(x,y);
                openSet.push(dziecko,dziecko.f);
            }
        }
        ////d4
        x = pom.position.rx();
        y = pom.position.ry()+1;
        if(x==-1){x = map->getMapSizeX()-1;}
        if(x==map->getMapSizeX()){x = 0;}
        if(y==-1){y = map->getMapSizeY()-1;}
        if(y==map->getMapSizeY()){y = 0;}
        if(map->getObstacleMap(y,x)==0){
            if(visitMap[y][x]==false){
                Node dziecko;
                dziecko.parentPosition = pom.position;
                dziecko.g = pom.g+1;
                dziecko.calculateH(destination);
                dziecko.f = dziecko.g+dziecko.h;
                dziecko.position = QPoint(x,y);
                openSet.push(dziecko,dziecko.f);
            }
        }


    }

    if(found){

        QList<QPoint> pathPoints;
        pathPoints.push_front(last.position);
        while(pathPoints[0]!=QPoint(-1,-1)){

            pathPoints.push_front(parentMap[pathPoints[0].ry()][pathPoints[0].rx()]);
        }
        pathPoints.pop_front();
        this->path.clear();

        for(int i=0;i<pathPoints.size()-1;i++){
            this->path.append(positionToDirection(pathPoints[i],pathPoints[i+1]));

        }

        if(path.size() == 0){
            this->nextDirection = 0;
            this->direction = 0;
        }

    }else{
        this->nextDirection = 0;
        this->direction = 0;
    }



}

void Ghost::DefaultChaseModeTicks()
{
    chaseMode = false;
    chaseModeTicks = 24;
    notChaseModeTicks = 24;

}

void Ghost::setChaseMode(bool mode)
{
    chaseMode = mode;
}

bool Ghost::getChaseMode()
{
    return chaseMode;
}

int Ghost::getChaseModeTicks()
{
    return chaseModeTicks;
}

int Ghost::getNotChaseModeTicks()
{
    return notChaseModeTicks;
}

void Ghost::nextChaseModeTicks()
{
    if(notChaseModeTicks>0)
        notChaseModeTicks-=2;

    if(notChaseModeTicks<0)
        notChaseModeTicks = 0;
}
