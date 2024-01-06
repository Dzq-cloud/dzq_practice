#include "cardispwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CarDispWidget w;
    w.show();

    return a.exec();
}
