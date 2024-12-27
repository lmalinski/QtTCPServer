#include "mytcpserver.h"

MyTCPServer::MyTCPServer(QObject *parent)
    : QObject{parent},
      m_server(this)
{
    connect(&m_server,SIGNAL(newConnection()),this,SLOT(slot_new_client()));
}

bool MyTCPServer::startListening(int port)
{
    m_port = port;
    m_isListening = m_server.listen(QHostAddress::Any, port);
    return m_isListening;
}

void MyTCPServer::stopListening()
{
    m_server.close();
}

void MyTCPServer::slot_new_client()
{
    QTcpSocket *client = m_server.nextPendingConnection();
    auto adr = client->peerAddress();
    emit newClientConnected(adr.toString());
}


