#ifndef MYCLIENT_H
#define MYCLIENT_H

// Импорт библиотек
#include <QWidget>
#include <QTcpSocket>

// Объявление нужных классов
class QTextEdit;
class QLineEdit;

// Определение класса MyClient, который наследуется от QWidget
class MyClient : public QWidget
{
    Q_OBJECT

public:
    // Конструктор, принимающий адрес сервера и порт
    MyClient(const QString& uri, int port, QWidget *parent = nullptr);
private:
    // Сокет
    QTcpSocket* m_pTcpSocket;
    // Поле вывода
    QTextEdit* m_ptxtInfo;
    // Поле ввода
    QLineEdit* m_ptxtInput;
    // Размер блока для чтения
    quint16 m_nNextBlockSize;
private slots:
    // Слот для обработки события готовности чтения данных от сервера
    void slotReadyRead();
    // Слот для обработки ошибок соединения
    void slotError (QAbstractSocket::SocketError);
    // Слот для отправки данных на сервер
    void slotSendToServer();
    // Слот для обработки события успешного подключения к серверу
    void slotConnected();
};
#endif // MYCLIENT_H
