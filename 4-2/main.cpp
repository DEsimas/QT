#include "mainwindow.h"
#include "exampleobject.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Атрибут нужен для корректного отображения размеров элементов на мониторах с большим разрешением
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // Приложение
    QApplication a(argc, argv);
    // Главное окно
    MainWindow w;
    // Показываем главное окно
    w.show();
    // Запускаем приложение
    return a.exec();
}
