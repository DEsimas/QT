#include <QApplication> // Приложение
#include <QDate> // Дата
#include <QTime> // Время
#include <QLabel> // Текстовая метка
#include <QString> // Строки

// Точка входа в программу
int main(int argc, char *argv[])
{
    // Создание экземпляра класса приложения с параметрами запуска
    QApplication a(argc, argv);
    // Создание объекта QDate с текущей датой
    QDate date = QDate::currentDate();
    // Создание объекта QTime с текущим временем
    QTime time = QTime::currentTime();
    // Создание объекта QString с информацией от текущей дате и времени
    QString string = date.toString() + " " + time.toString();
    // Создание объекта QLabel
    QLabel label(string);
    // Устанавливаем отступы для текстовой метки
    label.setMargin(50);
    // Отображаем текстовую метку
    label.show();
    //Запуск приложения
    return a.exec();
}
