#include <QtGui/QApplication>
#include "clock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Clock w;
//    w.resize(300, 300);
    w.show();

    return a.exec();
}
