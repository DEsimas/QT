#include "copymanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CopyManager manager(&a);
    manager.copy("input.dat", "output.dat");
    return a.exec();
}
