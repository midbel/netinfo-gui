#include "netwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setFamily(font.defaultFamily());
    font.setPointSize(9);
    a.setFont(font);

    NetWindow w;
    w.show();
    return a.exec();
}
