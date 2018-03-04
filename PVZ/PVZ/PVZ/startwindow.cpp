#include "startwindow.h"
#include "ui_startwindow.h"


startWindow::startWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startWindow)
{
    ui->setupUi(this);

    //背景设置
    surfaceImage = new QImage(":/new/startMenu/Surface.png");
    ui->label->setPixmap(QPixmap::fromImage(*surfaceImage));

    //开始游戏按钮设置
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(:/new/startMenu/WechatIMG1.png);}"
            "QPushButton:hover{border-image: url(:/new/startMenu/WechatIMG2.png);}"
            "QPushButton:pressed{border-image:url(:/new/startMenu/WechatIMG3.png);}");
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(showHandOfZoobie()));

    //从地里出来的手的动画设置
    movie_hand = new QMovie(":/new/startMenu/start.gif");
    ui->label_2->setMovie(movie_hand);
    ui->label_2->setScaledContents(true);

    //背景音乐设置
    mediaPlayer_backgroundMusic = new QMediaPlayer(this);
    mediaPlaylist_backgroundMusic = new QMediaPlaylist(this);
    mediaPlaylist_backgroundMusic->addMedia(QUrl("qrc:/new/music/Mountains.mp3"));
    mediaPlaylist_backgroundMusic->setCurrentIndex(1);
    mediaPlaylist_backgroundMusic->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaPlayer_backgroundMusic->setPlaylist(mediaPlaylist_backgroundMusic);
    mediaPlayer_backgroundMusic->setVolume(150);
    mediaPlayer_backgroundMusic->play();

    //邪恶叫声设置
    mediaPlayer_evilLaugh = new QMediaPlayer(this);
    mediaPlayer_evilLaugh->setMedia(QUrl("qrc:/new/music/evillaugh.mp3"));
    mediaPlayer_evilLaugh->setVolume(150);

}

//showhand
void startWindow::showHandOfZoobie()
{
    movie_hand->start();
    mediaPlayer_evilLaugh->play();
    gWindow = new GameWindow(this);

    QObject::connect(movie_hand,SIGNAL(finished()),mediaPlayer_backgroundMusic,SLOT(stop()));
    QObject::connect(movie_hand,SIGNAL(finished()),gWindow,SLOT(show()));

}
startWindow::~startWindow()
{
    delete ui;
}
