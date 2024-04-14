// Импорт библиотек
#include "myclient.h"
#include "ui_myclient.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QLineEdit>
#include <QPushButton>

// Конструктор класса MyClient, принимающий адрес сервера и порт
MyClient::MyClient(const QString& strHost, int nPort, QWidget* pwgt /*=0*/
) : QWidget(pwgt), m_nNextBlockSize(0)
{
    // Создаем новый объект QTcpSocket и пытаемся подключиться к указанному хосту и порту
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    // Подключаем сигналы от сокета к соответствующим слотам
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(slotError(QAbstractSocket::SocketError))
    );
    // Создаем виджеты для отображения информации и ввода текста
    m_ptxtInfo = new QTextEdit;
    m_ptxtInput = new QLineEdit;
    // Подключаем сигнал для отправки текста на сервер
    connect(m_ptxtInput, SIGNAL(returnPressed()),
        this, SLOT(slotSendToServer())
    );
    // Делаем QTextEdit только для чтения
    m_ptxtInfo->setReadOnly(true);
    // Создаем кнопку для отправки текста на сервер
    QPushButton* pcmd = new QPushButton("&Отправить");
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));
    // Настраиваем вертикальный макет для размещения виджетов
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Клиент</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);
}

// Слот для обработки события готовности чтения данных от сервера
void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;
        // Добавляем полученные данные в QTextEdit
        m_ptxtInfo->append(time.toString() + " " + str);
        m_nNextBlockSize = 0;
    }
}

// Слот для обработки ошибок соединения
void MyClient::slotError(QAbstractSocket::SocketError err)
{
    // Формируем сообщение об ошибке в зависимости от типа ошибки
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
        "The host was not found." : err == QAbstractSocket::RemoteHostClosedError ?
        "The remote host is closed." : err == QAbstractSocket::ConnectionRefusedError ?
        "The connection was refused." : QString(m_pTcpSocket->errorString())
    );
    // Добавляем сообщение об ошибке в QTextEdit
    m_ptxtInfo->append(strError);
}

// Слот для отправки данных на сервер
void MyClient::slotSendToServer()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    // Формируем блок данных для отправки
    out << quint16(0) << QTime::currentTime() << m_ptxtInput->text();
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    // Отправляем блок данных через сокет
    m_pTcpSocket->write(arrBlock);
    // Очищаем QLineEdit после отправки
    m_ptxtInput->setText("");
}

// Слот для обработки события успешного подключения к серверу
void MyClient::slotConnected()
{
    // Добавляем сообщение о подключении в QTextEdit
    m_ptxtInfo->append("Received the connected() signal");
}
