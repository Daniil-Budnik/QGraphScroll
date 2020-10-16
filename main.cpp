#include "QGraphScroll.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphScroll w;
    w.show();
    return a.exec();
}
