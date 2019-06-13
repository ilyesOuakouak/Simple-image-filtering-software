#include "create.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    create w;
    w.show();

    return a.exec();
}
