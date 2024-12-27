#ifndef SERVERMV_H
#define SERVERMV_H

#include <QMainWindow>

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

private:
    Ui::ServerMV *ui;
};
#endif // SERVERMV_H
