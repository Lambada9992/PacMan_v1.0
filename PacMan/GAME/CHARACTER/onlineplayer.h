#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include "GAME/CHARACTER/player.h"
#include <QTcpSocket>
#include <QObject>

/**
 * @brief The OnlinePlayer class klasa rozszerzajaca mozliwosci klasy player o komunikacje przez internet
 */
class OnlinePlayer :public QObject, public Player
{
    Q_OBJECT
private:
    //var
    QTcpSocket *socket;
    qintptr socketDesriptor;
    bool isConnected;
    QVector<bool> soundsToPlay;


    //methods
public:
    /**
     * @brief OnlinePlayer konstruktor
     * @param socket wskaznik na QTcpSocket
     * @param map wskaznik na mape gry
     * @param sound wskaznik na interfejs dzwiekowy
     * @param parent wskaznik na rodzica elementu
     */
    OnlinePlayer(QTcpSocket *socket,Board *map,SoundManager *sound,QObject *parent = nullptr);
    ~OnlinePlayer();

    /**
     * @brief soundPlayer metoda odtwarzajaca dzwiek o danym indeksie
     * @param i 1 - coin collect, 2 - bonus collect, 3 - die sound
     */
    virtual void soundPlayer(int i) override;

    //getery
    /**
     * @brief getSocketDescriptor metoda zwracajaca socketDescriptor polaczenia (QTcpSocket)
     * @return socketDescriptor
     */
    qintptr getSocketDescriptor();
    /**
     * @brief getIsConnected metoda zwracajaca stan polaczenia gracza
     * @return  true-polaczony, false-rozlaczony
     */
    bool getIsConnected();

private slots:
    void readyRead();
    void disconnected();
public slots:
    /**
     * @brief message metoda przesylajaca komende do gracza przez interfejs QTcpSocket
     * @param message wiadomosc
     */
    void message(QByteArray message);

signals:
    void join(qintptr socketDescriptor);
    void remove(qintptr socketDescriptor);
    void deletePlayer(qintptr socketDescriptor);
};

#endif // ONLINEPLAYER_H
