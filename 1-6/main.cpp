#include "blinklabel.h" // Моргающая текстовая метка

#include <QApplication> // Приложение

// Точка входа в программу
int main(int argc, char *argv[])
{
    // Создание экземпляра класса приложения с параметрами запуска
    QApplication a(argc, argv);
    // Создание объекта BlinkLabel
    BlinkLabel label("Sukharev Serafim, BST2202", 200);
    // Устанавливаем отступы для текстовой метки
    label.setMargin(50);
    // Отображение текстовой метки
    label.show();
    //Запуск приложения
    return a.exec();
}
