#include "widget.h"

#include <QApplication>
#include <QScreen>
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QScreen *qs=QApplication::primaryScreen();
    QRect rectangle = qs->geometry();
    int width = rectangle.width();
    int height = rectangle.height();


    Widget w;
    w.show();
    w.move(width/2-1200/2,height/2-800/2);
    return a.exec();
}
