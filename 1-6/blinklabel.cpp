// Подключение файла с описанием класса
#include "blinklabel.h"

// Событие окончания таймера
void BlinkLabel::timerEvent(QTimerEvent *)
{
   // Переключение состояния моргания
   this->isBlinking = !this->isBlinking;
   // Обновление текста метки
   this->setText(isBlinking ? this->string : "");
}

// Конструктор
BlinkLabel::BlinkLabel(QString string, int duration) : QLabel(string)
{
    // Изначальное состояние - текст виден
    this->isBlinking = true;
    // Устанавливаем строку
    this->string = string;
    // Запускаем таймер
    this->startTimer(duration);
}
