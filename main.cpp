#include "netwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetWindow w;
    w.show();
    return a.exec();
}
