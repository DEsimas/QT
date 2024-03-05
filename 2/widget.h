#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    // Конструктор
    Widget(QWidget *parent = nullptr);
    // Деструктор
    ~Widget();

private:
    // UI из формы
    Ui::Widget *ui;
    // Медиаплеер
    QMediaPlayer *player;
    // Плейлист для плеера
    QMediaPlaylist *playlist;
    // Модель плейлиста для его отображения в QTableView
    QStandardItemModel *playListModel;
    // Флаг, играет ли трек
    bool isPlaying;
    // Флаг, отключен ли звук
    bool isMuted;
};
#endif // WIDGET_H
