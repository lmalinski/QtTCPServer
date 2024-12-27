#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTCPServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTCPServer(QObject *parent = nullptr);
    bool startListening(int port);
    bool isListening() {return m_isListening;}
    void stopListening();

signals:
    void newClientConnected(QString adr);

private slots:
    void slot_new_client();
private:
    bool m_isListening = false;
    int m_port = 12345;
    QTcpServer m_server;
    QVector<QTcpSocket*> m_clients;
};

#endif // MYTCPSERVER_H
