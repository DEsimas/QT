#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Инициализация интерфейса
    ui->setupUi(this);
    // Соединение сигналов нажатий кнопок со слотами в MainWIndow
    connect(ui->sendMessage1, &QPushButton::clicked, this, &MainWindow::onWrite1Clicked);
    connect(ui->sendMessage2, &QPushButton::clicked, this, &MainWindow::onWrite2Clicked);
    connect(ui->start, &QPushButton::clicked, this, &MainWindow::on_start_clicked);
    connect(ui->stop, &QPushButton::clicked, this, &MainWindow::on_stop_clicked);
    // При старте потока запускаем код, при окончании выполнения кода уничтожаем поток
    connect(&thread_1, &QThread::started, &exampleObject_1, &ExampleObject::run);
    connect(&exampleObject_1, &ExampleObject::finished, &thread_1, &QThread::terminate);
    connect(&thread_2, &QThread::started, &exampleObject_2, &ExampleObject::run);
    connect(&exampleObject_2, &ExampleObject::finished, &thread_2, &QThread::terminate);
    // Соединяем сигнал отправки сообщения одного объекта, со слотом установки сообщения другого
    // Используется DirectConnection, чтобы выполнение сеттера происходило не в конце эвент лупа потока получателя,
    // а при отправке в потоке отправителя
    connect(&exampleObject_1, &ExampleObject::sendMessage, &exampleObject_2,
            &ExampleObject::setmessageFromAnotherThread, Qt::DirectConnection);
    connect(&exampleObject_2, &ExampleObject::sendMessage, &exampleObject_1,
            &ExampleObject::setmessageFromAnotherThread, Qt::DirectConnection);
    exampleObject_1.moveToThread(&thread_1);
    exampleObject_2.moveToThread(&thread_2);
}

MainWindow::~MainWindow()
{
    // Очистка памяти
    delete ui;
}

void MainWindow::onWrite1Clicked()
{
    // Запись сообщения в первый поток
    exampleObject_1.setmessageToSend(ui->message1->text());
}

void MainWindow::onWrite2Clicked()
{
    // Запись сообщения во второй поток
    exampleObject_2.setmessageToSend(ui->message2->text());
}

void MainWindow::on_start_clicked()
{
    // Запускаем оба потока
    thread_1.start();
    thread_2.start();
}

void MainWindow::on_stop_clicked()
{
    // Останавливаем оба потока
    exampleObject_1.setRunning(false);
    exampleObject_2.setRunning(false);
}

