#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "exampleobject.h"

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор
    MainWindow(QWidget *parent = nullptr);
    // Деструктор
    ~MainWindow();
private slots:
    // Слот нажатия на кнопку записи в первый поток
    void onWrite1Clicked();
    // Слот нажатия на кнопку записи во второй поток
    void onWrite2Clicked();
    // Слот нажатия на кнопку пуска потоков
    void on_start_clicked();
    // Слот нажатия на кнопку остановки потоков
    void on_stop_clicked();
private:
    // Объект пользовательского интерфейса
    Ui::MainWindow *ui;
    // Два потока
    QThread thread_1;
    QThread thread_2;
    // Два объекта, исполняющих код
    ExampleObject exampleObject_1;
    ExampleObject exampleObject_2;
};
#endif // MAINWINDOW_H
