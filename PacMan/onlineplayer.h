#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H


#include "player.h"
#include "myclient.h"

class OnlinePlayer : public Player
{
private:

    qintptr socketDescriptor;
    MyClient *client;

public:
    OnlinePlayer();
};

#endif // ONLINEPLAYER_H
