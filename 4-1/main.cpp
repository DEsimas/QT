#include "namedthread.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    // Создаем объект класса приложения
    QCoreApplication a(argc, argv);

    // Создаем три потока с разными именами
    NamedThread A("Thread1");
    NamedThread B("Thread2");
    NamedThread C("Thread3");

    // Запускаем созданные потоки на выполнение
    A.start();
    B.start();
    C.start();

    // Запускаем приложение
    return a.exec();
}
