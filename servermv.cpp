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
        m_server->stopListening();
        delete m_server;
    }
    m_server = new MyTCPServer(this);
    connect(m_server,SIGNAL(newClientConnected(QString)),this,SLOT(slot_newClientConnected(QString)));
    connect(m_server,SIGNAL(clientDisconnetced(int)),this,SLOT(slot_clientDisconnected(int)));
    connect(m_server,SIGNAL(newMsgFrom(QString,int)),this,SLOT(slot_newMsgFrom(QString,int)));
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
    if(m_server != nullptr && m_server->isListening())
    {
        m_server->stopListening();
        ui->startBut->setText("Start");
        ui->commBox->setEnabled(false);
    }
    else
    {
        int port = ui->portEdit->text().toInt();
        if(!validatePort(port))
            return;
        resetServer();
        if(!m_server->startListening(port))
            ui->statusbar->showMessage("Error starting server!");
        else
        {
            ui->startBut->setText("Stop");
            ui->commBox->setEnabled(true);
            ui->cliNum->setEnabled(false);
            ui->sendBut->setEnabled(false);
        }
    }
}

void ServerMV::updateCliNum()
{
    int numCli = m_server->getNumClients();
    ui->cliNum->setEnabled(numCli > 0);
    ui->sendBut->setEnabled(numCli > 0);
    ui->cliNum->setMaximum((numCli > 0)? (numCli-1) : 0);
}

void ServerMV::slot_newClientConnected(QString adr)
{
    ui->statusbar->showMessage("New client from: " + adr);
    updateCliNum();
}

void ServerMV::slot_clientDisconnected(int num)
{
    ui->statusbar->showMessage("Client " + QString::number(num) + " disconnected!");
    updateCliNum();
}

void ServerMV::slot_newMsgFrom(QString msg, int num)
{
    QString toWrite = "CL" + QString::number(num) + ": " + msg;
    ui->recEdit->append(toWrite);
}

void ServerMV::on_clrBut_clicked()
{
    ui->recEdit->clear();
}

void ServerMV::on_sendBut_clicked()
{
    int num = ui->cliNum->value();
    QString msg = ui->sendText->toPlainText();
    m_server->sendMsg(msg,num);
    ui->sendText->clear();
}

