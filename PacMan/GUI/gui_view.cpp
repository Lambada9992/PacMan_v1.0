#include "gui_view.h"

#include <QGraphicsSimpleTextItem>





#include <QDebug>
#include <QRegExpValidator>
#include <QTextEdit>
#include <QTimer>

GUI_View::GUI_View(QWidget *parent) : QGraphicsView(parent),
    m_scale(15)
{

    //window size and scrollbars

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(1024,900);
    setFixedSize(43*m_scale,33*m_scale);

    //creating scene
    scene = new QGraphicsScene(this);
    //scene->setSceneRect(0,0,1024,900);
    scene->setSceneRect(0,0,43*m_scale,33*m_scale);
    setScene(scene);

    scoreTable = nullptr;
    connectStatusText = nullptr;
    connectionModeText = nullptr;
    playersOnlineText = nullptr;
    spectatorOnlineText = nullptr;
    restartGameButton = nullptr;
    soundButton = nullptr;
    this->sound = &SoundManager::get();


    connect(&this->game,SIGNAL(update()),this,SLOT(updateGui()));
    connect(&this->game,SIGNAL(updateGui()),this,SLOT(updateGuiItems()));
    connect(&game,SIGNAL(hostStartedGame()),this,SLOT(displayGame()));

    //display mainmenu
    this->displayMainMenu();

}

GUI_View::~GUI_View()
{

    delete scene;

}

void GUI_View::displayMainMenu()
{
    if(scene == nullptr)return;
    game.setMode(0);
    sound->playMainMenuSound(true);

    //clearing
    scene->clear();clearItems();

    //bg patern and color
    this->setBackgroundBrush(QBrush(Qt::darkGray,Qt::SolidPattern));

    //title "PACMAN"
    QGraphicsTextItem *title = new QGraphicsTextItem(QString("PacMan"));
    QFont titleFont("comic sans",m_scale*4,QFont::Bold);
    title->setFont(titleFont);
    int x = this->width()/2 - title->boundingRect().width()/2;
    int y = m_scale;
    title->setPos(x,y);
    scene->addItem(title);


    //singleplayer button
    MyButton *singleplayerButton = new MyButton(QString("Single Player"));
    x = this->width()/2 - singleplayerButton->boundingRect().width()/2;
    y = 12*m_scale;
    singleplayerButton->setPos(x,y);
    connect(singleplayerButton,SIGNAL(clicked()),this,SLOT(singleplayerButtonClicked()));
    scene->addItem(singleplayerButton);

    //multiplayer button
    MyButton *multiplayerButton = new MyButton(QString("Multi Player"));
    x = this->width()/2 - multiplayerButton->boundingRect().width()/2;
    y = y+3*m_scale;
    multiplayerButton->setPos(x,y);
    connect(multiplayerButton,SIGNAL(clicked()),this,SLOT(multiplayerButtonClicked()));
    scene->addItem(multiplayerButton);

    //sound button
    soundButton = new MyButton(sound->getText());
    x = this->width()/2 - soundButton->boundingRect().width()/2;
    y = y+3*m_scale;
    soundButton->setPos(x,y);
    connect(soundButton,SIGNAL(clicked()),this,SLOT(soundButtonClicked()));
    scene->addItem(soundButton);


    //quit button
    MyButton *quitButton = new MyButton(QString("Quit"));
    x = this->width()/2 - quitButton->boundingRect().width()/2;
    y = y+3*m_scale;
    quitButton->setPos(x,y);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(quitButtonClicked()));
    scene->addItem(quitButton);

}

void GUI_View::updateScoreTable()
{
    if(scoreTable == nullptr)return;
    //if(game.getIsLive()==false)return;
    QString result = QString("SCORE TABLE:\n");

    for(int i=0;i<4;i++){
        if(game.getPlayerScoreText(i).length()!=0){
            if(i==0){
                result +="YELLOW ";
            }else if(i==1){
                result +="GREEN ";
            }else if(i==2){
                result +="PURPLE ";
            }else if(i==3){
                result +="BROWN ";
            }
            result +=game.getPlayerScoreText(i);
            result+= "\n";
        }
    }

    scoreTable->setPlainText(result);



}

void GUI_View::displayGame()
{
    if(scene == nullptr)return;
    sound->playMainMenuSound(false);
    //clearing
    scene->clear();
    clearItems();

    this->setBackgroundBrush(QBrush(Qt::darkGray,Qt::SolidPattern));

    this->sound->playBeginningSound();

    //game board
    board = new Gui_Board(m_scale,m_scale,m_scale,this->game);
    board->setFlag(QGraphicsItem::ItemIsFocusable);
    board->setFocus();
    connect(this,SIGNAL(updateCharacters(Game *)),board,SLOT(updateCharacters(Game *)));
    scene->addItem(board);

    //score table
    scoreTable = new QGraphicsTextItem(QString(""));
    QFont titleFont("comic sans",m_scale/2.0,QFont::Bold);
    scoreTable->setFont(titleFont);
    int x = 30*m_scale;
    int y = m_scale;
    scoreTable->setPos(x,y);
    scene->addItem(scoreTable);

    //sound button
    soundButton = new MyButton(sound->getText());
    x = 32*m_scale;
    y = 27*m_scale;
    soundButton->setPos(x,y);
    connect(soundButton,SIGNAL(clicked()),this,SLOT(soundButtonClicked()));
    scene->addItem(soundButton);


    //main menu button
    MyButton *mainMenuButton = new MyButton(QString("Main Menu"));
    x = 32*m_scale;
    y = 30*m_scale;
    mainMenuButton->setPos(x,y);
    connect(mainMenuButton,SIGNAL(clicked()),this,SLOT(mainMenuButtonClicked()));
    scene->addItem(mainMenuButton);



}

void GUI_View::singleplayerButtonClicked()
{
    game.setMode(1);
    displayGame();

    QTimer::singleShot(4000,&game,SLOT(start()));

}

void GUI_View::multiplayerButtonClicked()
{
    if(scene ==nullptr)return;

    scene->clear();clearItems();

    //Host Button
    MyButton *hostGameButton = new MyButton(QString("Host Game"));
    int x = this->width()/2 - hostGameButton->boundingRect().width()/2;
    int y = 9*m_scale;
    hostGameButton->setPos(x,y);
    connect(hostGameButton,SIGNAL(clicked()),this,SLOT(hostButtonClicked()));//////do poprawy
    scene->addItem(hostGameButton);

    //Join Button
    MyButton *joinGameButton = new MyButton(QString("Join Game"));
    x = this->width()/2 - joinGameButton->boundingRect().width()/2;
    y = y+3*m_scale;
    joinGameButton->setPos(x,y);
    connect(joinGameButton,SIGNAL(clicked()),this,SLOT(joinButtonClicked()));//////do poprawy
    scene->addItem(joinGameButton);

    //mainMenu Button
    MyButton *mainMenuButton = new MyButton(QString("Back"));
    x = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    y = 29*m_scale;
    mainMenuButton->setPos(x,y);
    connect(mainMenuButton,SIGNAL(clicked()),this,SLOT(mainMenuButtonClicked()));
    scene->addItem(mainMenuButton);

}

void GUI_View::quitButtonClicked()
{
    exit(0);
}

void GUI_View::mainMenuButtonClicked()
{
    game.stop();
    game.setMode(0);
    this->displayMainMenu();
}

void GUI_View::restartButtonClicked()
{
    game.restartGame();
    restartGameButton = nullptr;

    if(board){
        board->setFocus();
    }
}


void GUI_View::hostButtonClicked()
{
    if(scene == nullptr)return;

    scene->clear();clearItems();

    game.setMode(2);

    //connectStatusText
    playersOnlineText = new QGraphicsTextItem(QString("Online Players: 0"));
    QFont titleFont("comic sans",20,QFont::Bold);
    playersOnlineText->setFont(titleFont);
    int x = this->width()/2 - playersOnlineText->boundingRect().width()/2;
    int y = 4*m_scale;
    playersOnlineText->setPos(x,y);
    scene->addItem(playersOnlineText);

    //spectatorOnlineText
    spectatorOnlineText = new QGraphicsTextItem(QString("Spectators: 0"));
    titleFont = QFont("comic sans",20,QFont::Bold);
    spectatorOnlineText->setFont(titleFont);
    x = this->width()/2 - spectatorOnlineText->boundingRect().width()/2;
    y = 8*m_scale;
    spectatorOnlineText->setPos(x,y);
    scene->addItem(spectatorOnlineText);

    //startButton
    MyButton *startGameButton = new MyButton(QString("Start Game"));
    x = this->width()/2 - startGameButton->boundingRect().width()/2;
    y = 12*m_scale;
    startGameButton->setPos(x,y);
    connect(startGameButton,SIGNAL(clicked()),this,SLOT(startGameButtonClicked()));//////do poprawy
    scene->addItem(startGameButton);

    //mainMenu Button
    MyButton *mainMenuButton = new MyButton(QString("Back"));
    x = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    y = 29*m_scale;
    mainMenuButton->setPos(x,y);
    connect(mainMenuButton,SIGNAL(clicked()),this,SLOT(mainMenuButtonClicked()));
    scene->addItem(mainMenuButton);

}

void GUI_View::joinButtonClicked()
{
    if(scene ==nullptr)return;

    scene->clear();
    clearItems();

    game.setMode(3);

    //lineedit box
    lineEditBox = new QLineEdit();
    int xsize=7*m_scale,ysize=3*m_scale;

    int x = 10.5*m_scale - xsize/2.0;
    int y = 10*m_scale;
    lineEditBox->setGeometry(x,y,xsize,ysize);
    lineEditBox->setValidator( new QRegExpValidator(QRegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}")) );
    lineEditBox->setPlaceholderText("192.168.100.100");
    lineEditBox->setFocus();
    scene->addWidget(lineEditBox);

    //connect button
    MyButton *connectButton = new MyButton(QString("Connect"));
    x =  10.5*m_scale - connectButton->boundingRect().width()/2;
    y = y + ysize + m_scale;
    connectButton->setPos(x,y);
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connetButtonClicked()));
    scene->addItem(connectButton);

    //Player/Spectator button
    MyButton *playerSpectatorButton = new MyButton(QString("Player/Spectator"));
    x = 32.5*m_scale - playerSpectatorButton->boundingRect().width()/2;
    //y = 400;
    playerSpectatorButton->setPos(x,y);
    connect(playerSpectatorButton,SIGNAL(clicked()),this,SLOT(playerSpectatorButtonClicked()));
    scene->addItem(playerSpectatorButton);

    //connectStatusText
    connectStatusText = new QGraphicsTextItem(QString("Not Connected"));
    QFont titleFont("comic sans",20,QFont::Bold);
    connectStatusText->setFont(titleFont);
    x = 10.5*m_scale - connectStatusText->boundingRect().width()/2;
    y = 7*m_scale;
    connectStatusText->setPos(x,y);
    scene->addItem(connectStatusText);

    //connectionModeText
    connectionModeText = new QGraphicsTextItem(QString(""));
    titleFont = QFont("comic sans",20,QFont::Bold);
    connectionModeText->setFont(titleFont);
    x = 32.5*m_scale - connectionModeText->boundingRect().width()/2;
    //y = 100;
    connectionModeText->setPos(x,y);
    scene->addItem(connectionModeText);

    // back button
    MyButton *mainMenuButton = new MyButton(QString("Back"));
    x = this->width()/2 - mainMenuButton->boundingRect().width()/2;
    y = 29*m_scale;
    mainMenuButton->setPos(x,y);
    connect(mainMenuButton,SIGNAL(clicked()),this,SLOT(mainMenuButtonClicked()));
    scene->addItem(mainMenuButton);


}

void GUI_View::connetButtonClicked()
{
    if(lineEditBox==nullptr)return;
    game.connectToHost(lineEditBox->text());
}

void GUI_View::playerSpectatorButtonClicked()
{
    if(game.getIsOnlineParticipant()){
        game.playerSpectatorRequest(false);
    }else{
        game.playerSpectatorRequest(true);
    }

}

void GUI_View::startGameButtonClicked()
{
    game.setIsLiveAlready();
    game.sendInitState();
    this->displayGame();
    QTimer::singleShot(4500,&game,SLOT(start()));
}

void GUI_View::soundButtonClicked()
{
    sound->setIsMuted(!sound->getIsMuted());
    if(soundButton){
        soundButton->setText(sound->getText());
    }
    if(board){
        board->setFocus();
    }
}

void GUI_View::updateGui()
{
    emit updateCharacters(&game);
    if(scoreTable){
        updateScoreTable();
    }

}

void GUI_View::updateGuiItems()
{
    //multiplayer join screen
    if(connectStatusText){
        if(game.getConnectionState()==0){
           connectStatusText->setPlainText(QString("NOT CONNECTED"));
           connectStatusText->setDefaultTextColor(QColor(Qt::red));
           int x = 10.5*m_scale - connectStatusText->boundingRect().width()/2;
           int y = 7*m_scale;
           connectStatusText->setPos(x,y);
        }else if(game.getConnectionState()==2){
           connectStatusText->setPlainText(QString("CONNNECTED"));
           connectStatusText->setDefaultTextColor(QColor(Qt::green));
           int x = 10.5*m_scale - connectStatusText->boundingRect().width()/2;
           int y = 7*m_scale;
           connectStatusText->setPos(x,y);
        }else if(game.getConnectionState()==1){
            connectStatusText->setPlainText(QString("CONNNECTING ..."));
            connectStatusText->setDefaultTextColor(QColor(Qt::yellow));
            int x = 10.5*m_scale - connectStatusText->boundingRect().width()/2;
            int y = 7*m_scale;
            connectStatusText->setPos(x,y);
        }
    }

    if(connectionModeText){
        if(game.getConnectionState()==2){
            if(game.getIsOnlineParticipant()){
                connectionModeText->setPlainText("Mode: Player");
                int x = 32.5*m_scale - connectionModeText->boundingRect().width()/2;
                int y = 7*m_scale;
                connectionModeText->setPos(x,y);
            }else{
                connectionModeText->setPlainText("Mode: Spectator");
                int x = 32.5*m_scale - connectionModeText->boundingRect().width()/2;
                int y = 7*m_scale;
                connectionModeText->setPos(x,y);
            }
        }else{
            connectionModeText->setPlainText("");
        }
    }
    if(playersOnlineText){
        QString pom("Online Players: ");
        pom+=QString::number(game.getPLayerAmount());
        playersOnlineText->setPlainText(pom);
    }
    if(spectatorOnlineText){
        QString pom("Spectators: ");
        pom+=QString::number(game.getSpectatorAmount());
        spectatorOnlineText->setPlainText(pom);
    }

    if(game.ended() && game.getMode()!=0 && game.getMode()!=3){
        if(this->restartGameButton==nullptr){
            //restart button add
            restartGameButton = new MyButton(QString("Restart"));
            int x = 32*m_scale;
            int y = 24*m_scale;
            restartGameButton->setPos(x,y);
            connect(restartGameButton,SIGNAL(clicked()),this,SLOT(restartButtonClicked()));
            scene->addItem(restartGameButton);
        }
    }


    //check if ther is any gamecharacter to delete

}

void GUI_View::clearItems()
{
    board = nullptr;
    scoreTable = nullptr;
    connectStatusText = nullptr;
    connectionModeText = nullptr;
    playersOnlineText = nullptr;
    spectatorOnlineText = nullptr;
    restartGameButton = nullptr;
    soundButton = nullptr;
}

