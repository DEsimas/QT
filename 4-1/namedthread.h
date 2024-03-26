#ifndef NAMEDTHREAD_H
#define NAMEDTHREAD_H

#include <QThread>

// Класс наследуется от QThread
class NamedThread : public QThread
{
private:
    // Название потока
    QString name;
public:
    // Конструктор
    NamedThread(QString name);
    // Переопределение функции с кодом потока
    void run();
};

#endif // NAMEDTHREAD_H
