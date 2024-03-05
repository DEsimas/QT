#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    // Устанавливаем UI
    ui->setupUi(this);

    // Инициализируем флаги
    isPlaying = false;
    isMuted = false;

    // Устанавливаем иконки для кнопок
    ui->stopButton->setIcon(QIcon(":/Icons/stop.png")); // Стоп
    ui->prevButton->setIcon(QIcon(":/Icons/prev.png")); // Назад
    ui->playButton->setIcon(QIcon(":/Icons/play.png")); // Играть
    ui->nextButton->setIcon(QIcon(":/Icons/next.png")); // Вперед
    ui->muteButton->setIcon(QIcon(":/Icons/volume.png")); // Выкл. громкость

    // Устанавливаем название окна
    setWindowTitle("Сухарев Серафим БСТ2202");
    // Устанавливаем иконку окна
    setWindowIcon(QIcon(":/Icons/volume.png"));

    // Отключаем слайдер, показывающий прогресс по треку
    ui->durationSlider->setDisabled(true);

    // Создаем модель плейлиста
    playListModel = new QStandardItemModel(this);
    // Устанавливаем её в QTableView
    ui->playlistView->setModel(playListModel);

    // Настройка внешнего вида плейлиста
    // Скрываем колонку, в которой хранится путь к файлу
    ui->playlistView->hideColumn(1);
    // Скрываем нумерацию строк
    ui->playlistView->verticalHeader()->setVisible(false);
    // Включаем выделение строк
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Разрешаем выделять только одну строку
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Отключаем редактирование
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Включаем подгонку размера последней видимой колонки к ширине TableView
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);
    // Устанавливаем заголовки столбцов
    playListModel->setHorizontalHeaderLabels(QStringList() << tr("Название"));
    // Создаем плеер
    player = new QMediaPlayer(this);
    // Создаем плейлист
    playlist = new QMediaPlaylist(player);
    // Устанавливаем плееру плейлист
    player->setPlaylist(playlist);
    // Устанавливаем громкость
    player->setVolume(50);

    // Соединяем нужные сигналы со слотами
    // Нажатие кнопки добавить
    connect(ui->addButton, &QPushButton::clicked, this, [this]() {
        // С помощью диалога выбора файлов делаем множественный выбор mp3 файлов
        QStringList files = QFileDialog::getOpenFileNames(
            this, tr("Open files"), QString(), tr("Audio Files (*.mp3)"));
        // Далее устанавливаем данные в таблицу отображающую плейлист
        foreach (QString filePath, files) {
            // Строка с элементами
            QList<QStandardItem *> items;
            // Добавляем в строку имя трека
            items.append(new QStandardItem(QDir(filePath).dirName()));
            // Добавляем строку в модель плейлиста
            playListModel->appendRow(items);
            // Добавляем строку в плейлист
            playlist->addMedia(QUrl(filePath));
        }
    });
    // Нажатие кнопки стоп
    connect(ui->stopButton, &QToolButton::clicked, this, [this]() {
        isPlaying = false;
        player->stop();
    });
    // Нажатие кнопки назад
    connect(ui->prevButton, &QToolButton::clicked, playlist, &QMediaPlaylist::previous);
    // Нажатие кнопки играть
    connect(ui->playButton, &QToolButton::clicked, this, [this]() {
       isPlaying = !isPlaying;
       if(isPlaying) {
           player->play();
           ui->playButton->setIcon(QIcon(":/Icons/pause.png"));
       } else {
           player->pause();
           ui->playButton->setIcon(QIcon(":/Icons/play.png"));
       }
    });
    // Нажатие кнопки вперед
    connect(ui->nextButton, &QToolButton::clicked, playlist, &QMediaPlaylist::next);
    // Дабл клик по треку в плейлисте
    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index) {
        playlist->setCurrentIndex(index.row());
    });
    // Нажатие кнопки отключения звука
    connect(ui->muteButton, &QToolButton::clicked, this, [this]() {
         isMuted = !isMuted;
         if(isMuted) {
             ui->muteButton->setIcon(QIcon(":/Icons/novolume.png"));
             player->setVolume(0);
         } else {
             ui->muteButton->setIcon(QIcon(":/Icons/volume.png"));
             player->setVolume(ui->volumeSlider->value());
         }
    });
    // Изменение громкости
    connect(ui->volumeSlider, &QSlider::sliderMoved, this, [this](int volume) {
        if(!isMuted) {
            player->setVolume(volume);
        }
    });
    // При изменении длительности текущего трека
    connect(player, &QMediaPlayer::durationChanged, this, [this](qint64 duration) {
       // Устанавливаем диапазон движения слайдера
       ui->durationSlider->setRange(0, duration / 4.42);
    });
    // При изменении проигранной части трека
    connect(player, &QMediaPlayer::positionChanged, this, [this]() {
        // Устанавливаем нужную позицию слайдера слайдера
        ui->durationSlider->setValue(player->position());
    });
}

Widget::~Widget()
{
    // Очистка памяти
    delete ui;
    delete playListModel;
    delete playlist;
    delete player;
}

