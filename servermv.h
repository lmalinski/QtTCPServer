#ifndef SERVERMV_H
#define SERVERMV_H

#include <QMainWindow>

class MyTCPServer;

QT_BEGIN_NAMESPACE
namespace Ui {
class ServerMV;
}
QT_END_NAMESPACE

class ServerMV : public QMainWindow
{
    Q_OBJECT

public:
    ServerMV(QWidget *parent = nullptr);
    ~ServerMV();

private slots:
    void on_startBut_clicked();
    void slot_newClientConnected(QString adr);

private:
    bool validatePort(int port);
    void resetServer();

    Ui::ServerMV *ui;
    MyTCPServer *m_server = nullptr;
};
#endif // SERVERMV_H
