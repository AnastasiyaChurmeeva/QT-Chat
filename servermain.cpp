#include <QApplication>
#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server w;
    w.show();
    return a.exec();
}
