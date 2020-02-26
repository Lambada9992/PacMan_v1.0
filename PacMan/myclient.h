#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QThread>
#include <QTcpSocket>

class MyClient : public QThread
{
    Q_OBJECT

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

public:
    MyClient(QObject *parent = nullptr);
    void run() override;

public slots:
    void readyRead();
    void disconnected();

signals:


};

#endif // MYCLIENT_H
