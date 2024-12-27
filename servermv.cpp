#include "servermv.h"
#include "ui_servermv.h"
#include "mytcpserver.h"

ServerMV::ServerMV(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerMV)
{
    ui->setupUi(this);
}

ServerMV::~ServerMV()
{
    delete ui;
}

void ServerMV::resetServer()
{
    if(m_server != nullptr)
    {
        disconnect(m_server);
        m_server->stopListening();
        delete m_server;
    }
    m_server = new MyTCPServer(this);
    connect(m_server,SIGNAL(newClientConnected(QString)),this,SLOT(slot_newClientConnected(QString)));

}

bool ServerMV::validatePort(int port)
{
    if(port < 0 || 65535 < port)
    {
        ui->statusbar->showMessage("Invalid TCP port number!");
        return false;
    }
    return true;
}

void ServerMV::on_startBut_clicked()
{
    int port = ui->portEdit->text().toInt();
    if(!validatePort(port))
        return;
    resetServer();
    if(!m_server->startListening(port))
        ui->statusbar->showMessage("Error starting server!");
}

void ServerMV::slot_newClientConnected(QString adr)
{
    ui->statusbar->showMessage("New client from: " + adr);
}



