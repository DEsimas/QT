#include "namedthread.h"
#include <QDebug>

NamedThread::NamedThread(QString name)
{
    // Записываем имя потока в приватное поле
    this->name = name;
}

void NamedThread::run()
{
    // Имитируем работу потока
    for(int i = 0; i < 100; i++) {
        // Логируем данные с именем потока и изменяющимся значением
        qDebug() << "Thread:" << name << "\nValue of i: " << i << "\n";
    }
}
