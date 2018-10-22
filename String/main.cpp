#include "qmywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qMYWidget w;
    w.show();

    return a.exec();
}
