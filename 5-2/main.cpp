#include "myclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Инициализируем клиент с подключением к localhost на порте 2101
    MyClient w("localhost", 2101);
    // Устанавливаем размер окна
    w.resize(450, 500);
    // Устанавливаем заголовок окна
    w.setWindowTitle("БСТ2202 Сухарев Серафим");
    // Показываем окно
    w.show();
    return a.exec();
}
