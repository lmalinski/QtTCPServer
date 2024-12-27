#include "servermv.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerMV w;
    w.show();
    return a.exec();
}
