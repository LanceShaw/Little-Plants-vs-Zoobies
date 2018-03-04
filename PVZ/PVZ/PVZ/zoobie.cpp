#include "zoobie.h"


Zoobie::Zoobie(QWidget *parent): QLabel(parent)
{
    //僵尸吃东西的声音设置
    mediaPlayer_zoobieEating = new QMediaPlayer(this);
    mediaPlayer_zoobieEating->setMedia(QUrl("qrc:/new/music/chompsoft.mp3"));
    mediaPlayer_zoobieEating->setVolume(150);

    //僵尸只有两个基本动作
    zoobieMoveMovie = new QMovie(":/new/Zoobie/Zombie.gif");
    zoobieEatingMovie = new QMovie(":/new/Zoobie/ZombieAttack.gif");

    this->setMovie(zoobieMoveMovie);//初始化为移动的动作
    zoobieMoveMovie->start();

    this->move(posX,posY);//初始化移动到初始化点

    //计时器的设计
    zoobieTimer = new QTimer(this);
    zoobieTimer->setInterval(20);
    zoobieTimer->start();

    QObject::connect(zoobieTimer,SIGNAL(timeout()),this,SLOT(slot_zoobiePositionChange()));
    QObject::connect(zoobieTimer,SIGNAL(timeout()),this,SLOT(slot_zoobieActionChange()));

}

void Zoobie::slot_zoobiePositionChange()
{
    if(isEatingPlants == false)
    {
        posX = posX - movingSpeed;//没吃植物时才修改坐标
    }
    this->move(posX,posY);
}

void Zoobie::slot_zoobieActionChange()
{
    if(isEatingPlants == true)//在吃植物时的动作
    {
        mediaPlayer_zoobieEating->play();
        this->setMovie(zoobieEatingMovie);
        zoobieEatingMovie->start();
    }
    else
    {
        this->setMovie(zoobieMoveMovie);//初始化为移动的动作
        zoobieMoveMovie->start();
    }
}
