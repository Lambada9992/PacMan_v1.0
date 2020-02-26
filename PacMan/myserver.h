#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>


class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    MyServer(QObject *parent = nullptr);
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // MYSERVER_H
