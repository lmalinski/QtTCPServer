#include "servermv.h"
#include "ui_servermv.h"

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
