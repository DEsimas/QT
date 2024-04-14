#include "myserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Инициализируем сервер на порту 2101
    MyServer w(2101);
    // Устанавливаем размер окна
    w.resize(450, 500);
    // Устанавливаем заголовок окна
    w.setWindowTitle("БСТ2202 Сухарев Серафим");
    // Показываем окно
    w.show();
    return a.exec();
}
