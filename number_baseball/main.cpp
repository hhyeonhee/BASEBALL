#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(QTime::currentTime().msec());
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
