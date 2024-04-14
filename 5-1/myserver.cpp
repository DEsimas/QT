// Импорт библиотек
#include "myserver.h"
#include "ui_myserver.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>

// Конструктор класса, инициализирующий TCP сервер
MyServer::MyServer(int port, QWidget *parent)
    : QWidget(parent)
    , m_nNextBlockSize(0)
{
    // Создаем экземпляр класса QTcpServer
    m_ptcpServer = new QTcpServer(this);
    // При ошибке выдаем лог
    if (!m_ptcpServer->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(0,
            "Server Error",
            "Unable to start the server:"
            + m_ptcpServer->errorString()
        );
        m_ptcpServer->close();
        return;
    }
    // Соедининие слота обработки с сигналом создания нового соединения
    connect(m_ptcpServer, SIGNAL(newConnection()),
        this, SLOT(slotNewConnection())
    );
    // Создаем read only поле для вывода текста
    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);
    // Установка интерфейса
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Сервер</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}

// Слот, вызываемый при новом подключении клиента
void MyServer::slotNewConnection()
{
    // Получение сокета клиента
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    // Соединение сигнала и слота для отключения клиента
    connect(pClientSocket, SIGNAL(disconnected()),
        pClientSocket, SLOT(deleteLater())
    );
    // Его соединение сигнала на чтение со слотом обработки новых сообщений
    connect(pClientSocket, SIGNAL(readyRead()),
        this, SLOT(slotReadClient())
    );
    sendToClient(pClientSocket, "Server Response: Connected!");
}

// Слот для чтения данных от клиента
void MyServer::slotReadClient()
{
    // Получение сокета от отправителя
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    // Создание потока ввода
    QDataStream in(pClientSocket);
    // Установка версии потока
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        // Чтение размера одного блока данных
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
           }
           in >> m_nNextBlockSize;
        }
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime time;
        QString str;
        // Выводим сообщение из потока
        in >> time >> str;
        QString strMessage = time.toString() + " " + "Client has sent - " + str;
        // Выводим сообщение на экран
        m_ptxt->append(strMessage);
        // Зануляем переменную для чтения следующего блока данных
        m_nNextBlockSize = 0;
        // Отправляем сообщение на клиент
        sendToClient(pClientSocket,
            "Server Response: Received \"" + str + "\""
        );
    }
}

// Отправка данных клиенту
void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    // Создание массива байт
    QByteArray arrBlock;
    // Создание потока вывода
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    // Установка версии потока
    out.setVersion(QDataStream::Qt_4_2);
    // Запись времени и сообщения в поток
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    // Запись размера блока данных в поток
    out << quint16(arrBlock.size() - sizeof(quint16));
    // Отправка данных клиенту
    pSocket->write(arrBlock);
}
