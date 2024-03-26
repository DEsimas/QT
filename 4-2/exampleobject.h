#ifndef EXAMPLEOBJECT_H
#define EXAMPLEOBJECT_H

#include <QObject>

class ExampleObject : public QObject
{
    Q_OBJECT
    // running - флаг, идет ли исполнение
    // messageToSend - сообщение, которое будет отправлено в другой поток
    // messageFromAnotherThread - сообщение, полученное из другого потока
    // Создание свойства running с слотом-сеттером и сигналом при изменении
    Q_PROPERTY(
        bool running
        READ running
        WRITE setRunning
        NOTIFY runningChanged
    )
    // Создание свойства messageToSend с слотом-сеттером и сигналом при изменении
    Q_PROPERTY(
        QString messageToSend
        READ messageToSend
        WRITE setmessageToSend
        NOTIFY messageToSendChanged
    )
    // Создание свойства messageFromAnotherThread с слотом-сеттером и сигналом при изменении
    Q_PROPERTY(
        QString messageFromAnotherThread
        READ messageFromAnotherThread
        WRITE setmessageFromAnotherThread
        NOTIFY messageFromAnotherThreadChanged
    )
    // Приватное поле для свойства running
    bool _running;
    // Приватное поле для свойства messageToSend
    QString _messageToSend;
    // Приватное поля для свойства messageFromAnotherThread
    QString _messageFromAnotherThread;
    // Счётчик, имитирующий прогресс выполнения потока
    int count;
    // Имя потока
    QString name;
    // Блокирует выполнение потока на одну секунду
    void delay();
public:
    // Конструктор
    ExampleObject(QObject *parrent = nullptr);
    // Свойство running
    bool running() const;
    // Свойство messageToSend
    QString messageToSend() const;
    // Свойство messageFromAnotherThread
    QString messageFromAnotherThread() const;
signals:
    // При завершении выполнения
    void finished();
    // При изменении состояния выполнения
    void runningChanged(bool running);
    // При изменении сообщения для передачи
    void messageToSendChanged(QString messageToSend);
    // При изменении полученного сообщения
    void messageFromAnotherThreadChanged(QString messageFromAnotherThread);
    // При отправке сообщения
    void sendMessage(QString message);
public slots:
    // Запуск кода
    void run();
    // Изменение состояния выполнения
    void setRunning(bool running);
    // Изменение отправляемого сообщения
    void setmessageToSend(QString messageToSend);
    // Изменение полученного сообщения
    void setmessageFromAnotherThread(QString messageFromAnotherThread);
};

#endif // EXAMPLEOBJECT_H
