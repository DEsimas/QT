#include "exampleobject.h"

#include <QDebug>
#include <QTime>
#include <QCoreApplication>

void ExampleObject::delay()
{
    // Получаем время, до которого бездействуем
    QTime dieTime= QTime::currentTime().addSecs(1);
    // Ничего не делаем, пока текущее время не превзойдет полученное
    while (QTime::currentTime() < dieTime) {}
}

ExampleObject::ExampleObject(QObject *parrent) :
    // Инициализация родителя
    QObject(parrent),
    // Инициализация сообщений
    _messageToSend(""),
    _messageFromAnotherThread("")
{
}

// Геттеры, обеспечивают доступ к приватным полям через публичный интерфейс
bool ExampleObject::running() const
{
    return _running;
}

QString ExampleObject::messageToSend() const
{
    return _messageToSend;
}

QString ExampleObject::messageFromAnotherThread() const
{
    return _messageFromAnotherThread;
}

void ExampleObject::run()
{
    // Переводим состояние в активное
    setRunning(true);
    // Обнуляем счётчик
    count = 0;
    // Пока процесс запущен выполняем работу
    while(_running) {
        // Увеличиваем счетчик
        count++;
        qDebug() << "Message to send: " << _messageToSend << "\nRecieved message: "
                 << _messageFromAnotherThread << "\nProgress: " << count << "\n";
        delay();
    }
    emit finished();
}

// Сеттеры, позволяют изменять значение приватных полей через публичный интерфейс
// + подать сигнал об изменении
void ExampleObject::setRunning(bool running)
{
    if(running == _running)
        return;
    _running = running;
    emit runningChanged(_running);
}

void ExampleObject::setmessageToSend(QString message1)
{
    if(message1 == _messageToSend)
        return;
    _messageToSend = message1;
    emit messageToSendChanged(_messageToSend);
    // Отправить сообщение при изменении отправляемого текста
    emit sendMessage(_messageToSend);
}

void ExampleObject::setmessageFromAnotherThread(QString message2)
{
    if(message2 == _messageFromAnotherThread)
        return;
    _messageFromAnotherThread = message2;
    emit messageFromAnotherThreadChanged(_messageFromAnotherThread);
}
