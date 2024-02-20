// Подключение класса QApplication, нужного для старта приложения
#include <QApplication>
// Подключение класса QPushButton, представляющего виджет кнопки
#include <QPushButton>

/*
 * Точка входа в программу, как аргументы принимает строку
 * входных параметров при запуске из коммандной строки и ее длину
 */
int main(int argc, char *argv[])
{
    // Создание экземпляра класса приложения с параметрами запуска
    QApplication a(argc, argv);
    // Создание экземпляра класса виджета QPushButton
    QPushButton button("Hello, Serafim!");
    // Изменение размера виджета button
    button.resize(400, 200);
    // Отображение виджета button
    button.show();
    //Запуск приложения
    return a.exec();
}
