#ifndef BLINKLABEL_H
#define BLINKLABEL_H

#include <QLabel> // Текстовая метка
#include <QString> // Строка
#include <QTimerEvent> // Событие срабатывания таймера

// Класс BlinkLabel наследуется от QLabel и добавляет моргание виджета
class BlinkLabel : public QLabel
{
protected:
    // Флаг состояния моргания
    bool isBlinking;
    // Текст моргания
    QString string;
    // Метод, вызываемый после истечения таймера
    void timerEvent(QTimerEvent*);
public:
    // Конструктор, принимающий продолжительность моргания
    BlinkLabel(QString, int);
};

#endif // BLINKLABEL_H
