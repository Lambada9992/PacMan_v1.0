#include "ghost.h"
#include <QDebug>
#include "GAME/CHARACTER/mybucket.h"
#include "GAME/CHARACTER/mybucket.cpp"

bool Ghost::isFeared = false;

Ghost::Ghost(Board *map) : GameCharacter(map)
{
    //init players position
    playersPositions.resize(4);
    for(int i =0;i<4;i++){
        playersPositions[i] = QPoint(-1,-1);
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
    this->setNextDirection(1+rand()%4);
}

void Ghost::setPlayersPositions(const QVector<Player *>& players)
{
    for(int i = 0;i<players.size();i++){
        if(players[i]!=nullptr){
            if(players[i]->getIsAlive()){
                this->playersPositions[i] = players[i]->getPosition();
            }else{
                this->playersPositions[i] = QPoint(-1,-1);
            }
        }else{
            this->playersPositions[i] = QPoint(-1,-1);
        }
    }

}

void Ghost::setNextMove()
{

    if(Ghost::isFeared==false && this->position == this->spawnPosition){
        this->resurect();
    }

    if(Ghost::isFeared && (this->getIsAlive()==true)){
        this->randomNextDirection();
    }else{
        if(this->getIsAlive()==true){
            //finding closest player
            QPoint closestPlayer = QPoint(-1,-1);

            int distClosestPlayer;
            for(int i = 0 ;i<playersPositions.size();i++){
                if(playersPositions[i]!=QPoint(-1,-1)){
                    if(closestPlayer == QPoint(-1,-1)){
                        closestPlayer = playersPositions[i];
                        distClosestPlayer = (this->position.rx()-closestPlayer.rx())*(this->position.rx()-closestPlayer.rx());
                        distClosestPlayer += (this->position.ry()-closestPlayer.ry())*(this->position.ry()-closestPlayer.ry());
                    }else{
                        int distCurrent = (this->position.rx()-playersPositions[i].rx())*(this->position.rx()-playersPositions[i].rx());
                        if(distCurrent < distClosestPlayer){
                            closestPlayer = playersPositions[i];
                            distClosestPlayer = distCurrent;
                        }
                    }
                }
            }
            //if ther is no players
            if(closestPlayer == QPoint(-1,-1)){
                this->randomNextDirection();
                return;
            }


            //set path to closest player or spawn point
            this->generetePathToPoint(closestPlayer);
        }else{
            this->generetePathToPoint(this->spawnPosition);
        }

        if(path.size()!=0){
            this->nextDirection = path[0];
            path.pop_front();
        }


    }

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
