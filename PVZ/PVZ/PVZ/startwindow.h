#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include "QMediaPlayer"
#include "QMediaPlaylist"
#include "QMovie"

namespace Ui {
class startWindow;
}

class startWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit startWindow(QWidget *parent = 0);
    ~startWindow();
    GameWindow *gWindow;

    QMediaPlayer *mediaPlayer_backgroundMusic;//media控制
    QMediaPlaylist *mediaPlaylist_backgroundMusic;//连续播放的list
    QMediaPlayer *mediaPlayer_evilLaugh;//邪恶叫声

    QMovie* movie_hand;

    QImage *surfaceImage;

public slots:
    void showHandOfZoobie();
private:
    Ui::startWindow *ui;

};

#endif // STARTWINDOW_H
