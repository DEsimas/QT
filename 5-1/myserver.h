#ifndef MYSERVER_H
#define MYSERVER_H

// Импорт библиотек
#include <QWidget>

// Объявление нужных классов
class QTcpServer;
class QTextEdit;
class QTcpSocket;

// Определение класса MyServer, который наследуется от QWidget
class MyServer : public QWidget
{
    Q_OBJECT
private:
    QTcpServer* m_ptcpServer; // Сервер
    QTextEdit* m_ptxt; // Поле для ввода текста
    quint16 m_nNextBlockSize; // Размер блока для чтения
    void sendToClient(QTcpSocket* pSocket, const QString& str); // Функция отправки сообщений на клиент
public:
    MyServer(int port, QWidget *parent = nullptr); // Конструктор класса с портом
public slots:
    virtual void slotNewConnection(); // Слот для обработки нового входящего соединения
    void slotReadClient(); // Слот для чтения данных от клиента
};
#endif // MYSERVER_H
