#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    // Получаем текущее время
    QTime time = QTime::currentTime();
    // Стартуем таймер на время, оставшееся до переключения секунды
    this->startTimer(1000 - time.msec());
    // Выводим время
    this->ui->label->setText(time.toString());
    // Взводим флаг
    this->isFirstTimer = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* timer)
{
    // Если таймер первый, то убиваем его и стартуем секундный
    if(this->isFirstTimer) {
        this->isFirstTimer = false;
        this->killTimer(timer->timerId());
        this->startTimer(1000);
    }
    // Получаем текущее время
    QTime time = QTime::currentTime();
    // Выводим новое время
    this->ui->label->setText(time.toString());
}
