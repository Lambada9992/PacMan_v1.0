#include "game.h"
#include <QDebug>

Game::Game()
{
    //var init
    players.resize(4);
    ghosts.resize(4);
    for(int i = 0;i<players.size();i++){
        players[i] = nullptr;
    }
    for(int i=0;i<ghosts.size();i++){
        ghosts[i] = nullptr;
    }
    this->mode = 0;
    this->timer = nullptr;
    this->timerInterval = 0;
    this->isLive = false;
    this->fearTime = 5000;
    this->fearState = 0;
    this->server = nullptr;
    this->socket = nullptr;
    this->connectionState = 0;
    this->isOnlineParticipant = false;

}

Game::~Game()
{
    clear();
}

void Game::setMode(unsigned int mode)
{
    clear();
    switch(mode){
    case 1:
        this->mode = 1;

        //timer Initialization
        this->timer = new QTimer();
        timer->setInterval(100);
        timerInterval = 100;
        connect(timer,SIGNAL(timeout()),this,SLOT(onTick()));

        //MyPlayer Initialization
        myPlayerIndex = 0;
        players[0] = new MyPlayer(&playground);
        players[0]->setSpawnPosition(playground.getSpawnPoint(0));

        //ghosts initialization
        ghosts[0]= new Ghost(&playground);
        ghosts[0]->setSpawnPosition(playground.getSpawnPoint(4+0));
        ghosts[1]= new Ghost(&playground);
        ghosts[1]->setSpawnPosition(playground.getSpawnPoint(4+1));
        ghosts[2]= new Ghost(&playground);
        ghosts[2]->setSpawnPosition(playground.getSpawnPoint(4+2));
        ghosts[3]= new Ghost(&playground);
        ghosts[3]->setSpawnPosition(playground.getSpawnPoint(4+3));

        //qDebug() << this->getInitStateOnline().toUtf8();


        break;
    case 2:
        ////////////////////////do zmiany
        this->mode = 2;

        //timer initialization
        this->timer = new QTimer();
        timer->setInterval(100);
        timerInterval = 100;
        connect(timer,SIGNAL(timeout()),this,SLOT(onTick()));



        server = new QTcpServer(this);
        connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
        server->listen(QHostAddress::Any,1234);

        myPlayerIndex = 0;
        players[0] = new MyPlayer(&playground);
        players[0]->setSpawnPosition(playground.getSpawnPoint(0));

        //one ghost for now

        ghosts[0]= new Ghost(&playground);
        ghosts[0]->setSpawnPosition(playground.getSpawnPoint(4+0));
        ghosts[1]= new Ghost(&playground);
        ghosts[1]->setSpawnPosition(playground.getSpawnPoint(4+1));
        ghosts[2]= new Ghost(&playground);
        ghosts[2]->setSpawnPosition(playground.getSpawnPoint(4+2));
        ghosts[3]= new Ghost(&playground);
        ghosts[3]->setSpawnPosition(playground.getSpawnPoint(4+3));

        break;
    case 3:
        this->mode = 3;
        socket = new QTcpSocket();
        connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));


        break;
    default:
        this->mode = 0;

        break;
    }
}

void Game::clear()
{
    //map clear
    playground.setMap(1);
    //

    for(int i = 0;i<players.size();i++){
        if(players[i] != nullptr){
            if(dynamic_cast<OnlinePlayer *>(players[i]) == NULL)delete players[i];
            players[i] = nullptr;
        }
    }
    for(int i = 0;i<ghosts.size();i++){
        if(ghosts[i] != nullptr){
            delete ghosts[i];
            ghosts[i] = nullptr;
        }
    }
    if(timer!=nullptr){
        delete timer;
        timer= nullptr;
    }
    if(server!=nullptr){
        delete server;
        server = nullptr;
    }

    this->allConectedPlayers.removeAll(nullptr);
    for(int i =0;i<allConectedPlayers.size();i++){
        delete allConectedPlayers[i];
    }
    this->allConectedPlayers.clear();

    if(socket!=nullptr){
        socket->deleteLater();
        socket = nullptr;
    }



}

bool Game::ended()
{
    if(playground.isAllBonusCollected())return true;

    for(int i =0;i<players.size();i++){
        if(players[i]!=nullptr){
            if(players[i]->getIsAlive()==true)return false;;
        }
    }

    return true;

}

void Game::myPlayerControl(int direction)
{
    if(this->mode == 0)return;


    if(mode!=3){
        if(!isLive)return;//zwrócic uwage
        players[myPlayerIndex]->setNextDirection(direction);
    }else{
        if(socket!=nullptr){
            if(socket->state()==QTcpSocket::ConnectedState){
                switch(direction){
                case 1:
                    socket->write("w");
                    break;
                case 2:
                    socket->write("d");
                    break;
                case 3:
                    socket->write("s");
                    break;
                case 4:
                    socket->write("a");
                    break;
                }
                socket->waitForBytesWritten(1000);
            }
        }
    }
}

void Game::setIsLiveAlready()
{
    this->isLive = true;
}

void Game::start()
{
    if(mode==0)return;
    this->isLive = true;
    timer->start();
}

void Game::stop()
{
    if(mode==0)return;
    this->isLive = false;
    timer->stop();
}

void Game::makeMoves()
{
    for(int i =0;i<players.size();i++){
        if(players[i]!=nullptr){
            if(!players[i]->getIsAlive())continue;
            players[i]->move();
            if(players[i]->collectBonuses()){
                Ghost::isFeared=true;
                fearState++;
                QTimer::singleShot(fearTime,this,SLOT(cancelFear()));

            }
        }
    }

    this->colisions();

    for(int i =0;i<ghosts.size();i++){
        if(ghosts[i]!=nullptr){
            ghosts[i]->setPlayersPositions(players);
            ghosts[i]->setNextMove();
            ghosts[i]->move();
        }
    }

    this->colisions();

}

void Game::colisions()
{
    for(int i =0;i<players.size();i++){

        if(players[i]==nullptr)continue;

        if(players[i]->getIsAlive()==false)continue;

        for(int j =0 ;j<ghosts.size();j++){

            if(ghosts[j]==nullptr)continue;

            if(ghosts[j]->getIsAlive()==false)continue;

            if(players[i]->getPosition()!=ghosts[j]->getPosition())continue;

            if(Ghost::isFeared == false){
                players[i]->kill();
            }else{
                ghosts[j]->kill();
            }

        }

    }

}

GameCharacter *Game::character(unsigned int index)
{
    if(index>=0 && index <players.size())return players[index];
    if(index>=players.size() && index <players.size()+ghosts.size())return ghosts[index-players.size()];//tu jak zaneguje to się nie wywala
    return nullptr;
}

unsigned int Game::amountOfChracters()
{
    return this->players.size()+this->ghosts.size();
}

bool Game::isAnyPlayerAlive()
{
    for(int i = 0;i<players.size();i++){
        if(players[i]==nullptr)continue;
        if(players[i]->getIsAlive())return true;
    }
    return false;
}

int Game::getTimerInterval()
{
    return this->timerInterval;
}

QString Game::getPlayerScoreText(const unsigned int playerIndex)
{
    QString result = QString("");
    if(playerIndex>=players.size())return result;
    if(players[playerIndex]==nullptr)return result;
    result += "Life: ";
    result += QString::number(players[playerIndex]->getLife());
    result += "  Score: ";
    result += QString::number(players[playerIndex]->getScore());
    result += "  ";
    if(players[playerIndex]->getIsAlive()==false){result += "DEAD";}

    return result;
}

bool Game::getIsLive()
{
    return this->isLive;
}

void Game::resetLevel()
{
    for(int i = 0; i<players.size();i++){
        if(players[i]==nullptr)continue;
        if(players[i]->getLife()>0){players[i]->resurect();}
    }

    for(int i = 0 ;i<ghosts.size();i++){
        if(ghosts[i]==nullptr)continue;
        ghosts[i]->goSpawn();
        ghosts[i]->resurect();
    }

    Ghost::isFeared = false;
}


QString Game::getInitStateOnline()
{
    QString result="";

    result.append("%M;");
    result.append(std::to_string(playground.getMapIndex()).c_str());
    //result.append(";");

    result.append("%T;");
    result.append(std::to_string(this->getTimerInterval()).c_str());

    result.append("%F;");
    result.append((std::to_string(0)).c_str());

    for(int i =0;i<this->amountOfChracters();i++){
        if(character(i)==nullptr)continue;
        if(dynamic_cast<Player *>(character(i))!=NULL){
            result.append("%NP;");
            result.append(std::to_string(i).c_str());
            result.append(";");
            Player *pom = dynamic_cast<Player *>(character(i));
            result.append(std::to_string(pom->getPosition().rx()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getPosition().ry()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getLife()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getScore()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getIsAlive()).c_str());

        }else{
            result.append("%NG;");
            int index = i-4;
            result.append(std::to_string(index).c_str());
            result.append(";");
            Ghost * pom = dynamic_cast<Ghost *>(character(i));
            result.append(std::to_string(pom->getPosition().rx()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getPosition().ry()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getIsAlive()).c_str());
        }

    }

    return result;

}

void Game::setInitStateOnline(QString initState)
{
    //clear for sure
    for(int i = 0;i<players.size();i++){
        if(players[i] != nullptr){
            if(players[i]!=nullptr)delete players[i];
            players[i] = nullptr;
        }
    }
    for(int i = 0;i<ghosts.size();i++){
        if(ghosts[i] != nullptr){
            delete ghosts[i];
            ghosts[i] = nullptr;
        }
    }

    //
    initState.replace("init","");
    //initState = initState.mid(4);///////////////////////////to check
    QStringList pom = initState.split('%');
    for(int i =0;i<pom.length();i++){
        interpretOnlineComand(pom[i]);
    }





}

QString Game::getStateOnline()
{
    QString result="";

    result.append("%F;");
    result.append((std::to_string(Ghost::isFeared)).c_str());

    for(int i =0;i<this->amountOfChracters();i++){
        if(character(i)==nullptr)continue;
        if(dynamic_cast<Player *>(character(i))!=NULL){
            result.append("%P;");
            result.append(std::to_string(i).c_str());
            result.append(";");
            Player *pom = dynamic_cast<Player *>(character(i));
            result.append(std::to_string(pom->getPosition().rx()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getPosition().ry()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getLife()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getScore()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getIsAlive()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getDirection()).c_str());

        }else{
            result.append("%G;");
            int index = i-4;
            result.append(std::to_string(index).c_str());
            result.append(";");
            Ghost * pom = dynamic_cast<Ghost *>(character(i));
            result.append(std::to_string(pom->getPosition().rx()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getPosition().ry()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getIsAlive()).c_str());
            result.append(";");
            result.append(std::to_string(pom->getDirection()).c_str());
        }

    }

    return result;


}

void Game::setStateOnline(QString state)
{
    state.replace("state","");
    QStringList pom = state.split('%');
    for(int i =0;i<pom.length();i++){
        interpretOnlineComand(pom[i]);
    }
}

void Game::interpretOnlineComand(QString command)
{
    QStringList var=command.split(';');

    if(var[0]=="P"){
        int index = std::stoi(var[1].toStdString());
        players[index]->setPosition(std::stoi(var[3].toStdString()),std::stoi(var[2].toStdString()));
        players[index]->setSpawnPosition(players[index]->getPosition());
        players[index]->setLife(std::stoi(var[4].toStdString()));
        players[index]->setScore(std::stoi(var[5].toStdString()));
        players[index]->setIsAlive(std::stoi(var[6].toStdString()));
        players[index]->setDirection(std::stoi(var[7].toStdString()));
        return;
    }
    if(var[0]=="G"){
        int index = std::stoi(var[1].toStdString());

        ghosts[index]->setPosition(std::stoi(var[3].toStdString()),std::stoi(var[2].toStdString()));
        ghosts[index]->setSpawnPosition(ghosts[index]->getPosition());
        ghosts[index]->setIsAlive(std::stoi(var[4].toStdString()));
        ghosts[index]->setDirection(std::stoi(var[5].toStdString()));
        return;
    }
    if(var[0]=='F'){
        Ghost::isFeared = std::stoi(var[1].toStdString());
        return;
    }
    if(var[0]=='M'){
        this->playground.setMap(std::stoi(var[1].toStdString()));
        return;
    }
    if(var[0]=='T'){
        timerInterval = std::stoi(var[1].toStdString());
        return;
    }
    if(var[0]=="NP"){

        int index = std::stoi(var[1].toStdString());
        players[index] = new Player(&playground);
        players[index]->setPosition(std::stoi(var[3].toStdString()),std::stoi(var[2].toStdString()));
        players[index]->setSpawnPosition(players[index]->getPosition());
        players[index]->setLife(std::stoi(var[4].toStdString()));
        players[index]->setScore(std::stoi(var[5].toStdString()));
        players[index]->setIsAlive(std::stoi(var[6].toStdString()));
        return;
    }
    if(var[0]=="NG"){

        int index = std::stoi(var[1].toStdString());
        ghosts[index] = new Ghost(&playground);
        ghosts[index]->setPosition(std::stoi(var[3].toStdString()),std::stoi(var[2].toStdString()));
        ghosts[index]->setSpawnPosition(ghosts[index]->getPosition());
        ghosts[index]->setIsAlive(std::stoi(var[4].toStdString()));
        return;
    }

}

bool Game::getIsOnlineParticipant()
{
    return isOnlineParticipant;
}

void Game::playerSpectatorRequest(bool status)
{
    if(socket!=nullptr){
        if(socket->state()==QTcpSocket::ConnectedState){
            if(status){
                socket->write("j");
            }else{
                socket->write("r");
            }
            socket->waitForBytesWritten(1000);
        }
    }
}

void Game::sendInitState()
{
    QString var = "init";
    var.append(getInitStateOnline());
    emit messageAll(var.toUtf8());
}

void Game::sendStatePacket()
{
    QString var = "state";
    var.append(getStateOnline());
    emit messageAll(var.toUtf8());
}

void Game::onTick()
{

    makeMoves();
    emit update();
    if(mode==2){sendStatePacket();}

    if(playground.isAllBonusCollected()){
        this->stop();
        //go to next level
        emit update();


    }

    if(!isAnyPlayerAlive()){
        resetLevel();
        if(!isAnyPlayerAlive()){
            this->stop();
            emit update();
        }
    }



}

void Game::cancelFear()
{
    if(fearState==1){
        Ghost::isFeared = false;
        fearState--;
    }else{
        fearState--;
    }
}

void Game::newConnection()
{
    OnlinePlayer *pom = new OnlinePlayer(server->nextPendingConnection(),&playground);
    connect(pom,SIGNAL(join(qintptr)),this,SLOT(onlinePlayerJoin(qintptr)));
    connect(pom,SIGNAL(remove(qintptr)),this,SLOT(onlinePlayerRemove(qintptr)));
    connect(pom,SIGNAL(deletePlayer(qintptr)),this,SLOT(onlinePlayerDelete(qintptr)));
    connect(this,SIGNAL(messageAll(QByteArray)),pom,SLOT(message(QByteArray)));
    this->allConectedPlayers.append(pom);

}

void Game::onlinePlayerJoin(qintptr socketDescriptor)
{
    if(this->isLive == true) return;
    OnlinePlayer *requestingPlayer = nullptr;

    for(int i = 0;i<allConectedPlayers.size();i++){
        if(allConectedPlayers[i]->getSocketDescriptor()==socketDescriptor){
            requestingPlayer = allConectedPlayers[i];
            break;
        }
    }

    if(requestingPlayer==nullptr)return;

    for(int i =0;i<players.size();i++){
        if(players[i]!=nullptr){
            OnlinePlayer *pom = dynamic_cast<OnlinePlayer *>(players[i]);
            if(pom!= NULL){
                if(pom->getSocketDescriptor()==socketDescriptor)return;
            }
        }
    }

    for(int i = 0;i<players.size();i++){
        if(players[i]==nullptr){
            players[i] = requestingPlayer;
            players[i]->setSpawnPosition(this->playground.getSpawnPoint(i));
            requestingPlayer->message("join accept");
            return;
        }
    }
}

void Game::onlinePlayerRemove(qintptr socketDescriptor)
{
    for(int i = 0;i<players.size();i++){
        OnlinePlayer *pom=dynamic_cast<OnlinePlayer *>(players[i]);
        if(pom!=NULL){
            if(pom->getSocketDescriptor()==socketDescriptor){
                pom->message("remove accept");//to delete
                players[i] = nullptr;
            }
        }
    }
}

void Game::onlinePlayerDelete(qintptr socketDescriptor)
{
    this->onlinePlayerRemove(socketDescriptor);

    for(int i = 0;i<allConectedPlayers.size();i++){
        if(allConectedPlayers[i] == nullptr)continue;

        if(allConectedPlayers[i]->getSocketDescriptor()==socketDescriptor){
            allConectedPlayers[i]->message("delete");//to delete
            delete allConectedPlayers[i];
            allConectedPlayers[i] = nullptr;
            allConectedPlayers.removeAll(nullptr);

        }
    }
}

void Game::connectToHost(QString ip, qint16 port)
{
    if(socket == nullptr){
        connectionState = 0;
        return;
    }
    connectionState = 0;
    emit updateGui();

    if(socket->state()==QTcpSocket::ConnectedState){
        socket->close();
    }
    socket->connectToHost(ip,port);
    connectionState = 1;
    emit updateGui();
    this->isOnlineParticipant = false;

    if(socket->waitForConnected(5000)){
        connectionState = 2;
        emit updateGui();
    }else{
        connectionState = 0;
        emit updateGui();
    }
}

void Game::readyRead()
{
    QString pom;
    pom = socket->readAll();
    qDebug() << pom;

    if(pom.mid(0,5)=="state"){this->setStateOnline(pom);emit update();return;}
    if(pom=="join accept"){this->isOnlineParticipant=true;emit updateGui();return;}
    if(pom=="remove accept"){this->isOnlineParticipant=false;emit updateGui();return;}
    if(pom.mid(0,4)=="init"){this->setInitStateOnline(pom);emit hostStartedGame();return;}
}

void Game::disconnected()
{
    this->isOnlineParticipant = false;
}

