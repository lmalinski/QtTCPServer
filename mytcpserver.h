#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>

class MyTCPServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTCPServer(QObject *parent = nullptr);

signals:
};

#endif // MYTCPSERVER_H
