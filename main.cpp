#include "commute.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Commute w;
    w.show();

    return a.exec();
}
