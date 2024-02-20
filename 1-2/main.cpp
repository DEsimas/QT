// Подключение класса QApplication, нужного для старта приложения
#include <QApplication>
// Подключение класса QLabel, представляющего виджет текстовой метки
#include <QLabel>

/*
 * Точка входа в программу, как аргументы принимает строку
 * входных параметров при запуске из коммандной строки и ее длину
 */
int main(int argc, char *argv[])
{
    // Создание экземпляра класса приложения с параметрами запуска
    QApplication a(argc, argv);
    // Создание экземпляра класса виджета QLabel
    QLabel* label = new QLabel("Hello, BST2202, Sukharev Serafim");
    // Добавим текстовой метке отступы
    label->setMargin(30);
    // Отображение виджета label
    label->show();
    //Запуск приложения
    return a.exec();
}
