#include "polevaultingzoobie.h"

PoleVaultingZoobie::PoleVaultingZoobie(QWidget *parent):Zoobie(parent)
{
    //参数设定
    this->life = 430;
    this->movingSpeed = 0.2;

    //动画设定
    this->zoobieMoveMovie = new QMovie(":/new/PoleVaultingZoobie/PoleVaultingZombie.gif");
    this->zoobieEatingMovie = new QMovie(":/new/PoleVaultingZoobie/PoleVaultingZombieAttack.gif");
    this->zoobieVaultingMovie = new QMovie(":/new/PoleVaultingZoobie/jumpzombiejump.gif");
    this->vaultingZoobieWalkMovie = new QMovie(":/new/PoleVaultingZoobie/PoleVaultingZombieWalk.gif");

    //跳跃声音判定
    mediaPlayer_zoobieVaulting = new QMediaPlayer(this);
    mediaPlayer_zoobieVaulting->setMedia(QUrl("qrc:/new/music/polevault.mp3"));
    mediaPlayer_zoobieVaulting->setVolume(150);

    //位置设定
    this->setGeometry(posX,posY,223,144);
    this->setScaledContents(true);

    QObject::connect(zoobieTimer,SIGNAL(timeout()),this,SLOT(slot_zoobiePositionChange()));
    QObject::connect(zoobieTimer,SIGNAL(timeout()),this,SLOT(slot_zoobieActionChange()));

}

//改变flag
void PoleVaultingZoobie::slot_changePoleVaultingZoobieFlag()
{
    isToVault = false;
    hasVaulted = true;
}
//僵尸位置改变
void PoleVaultingZoobie::slot_zoobiePositionChange()
{
    if( hasVaulted == false && isEatingPlants == false && isToVault == false)//遇到第一个植物前，正常走路时
    {
        posX = posX - movingSpeed;
        this->move(posX,posY);
    }
    if( isToVault == true)//遇到第一个植物，跳跃
    {
        posX = posX - 0.25*movingSpeed;
        this->move(posX,posY);
    }
    if(hasVaulted == true && isEatingPlants == false && isToVault == false)//跳过第一个植物后，正常走路时
    {
        posX = posX - 0.5 * movingSpeed;
        this->move(posX,posY);
    }
    if(hasVaulted == true && isEatingPlants == true && isToVault == false)//跳过第一个植物后，吃东西时
    {
        posX = posX - 0;
        this->move(posX,posY);
    }
}

//僵尸动作改变
void PoleVaultingZoobie::slot_zoobieActionChange()
{
    if( hasVaulted == false && isEatingPlants == false && isToVault == false)//遇到第一个植物前，正常走路时
    {
        this->setMovie(zoobieMoveMovie);
        zoobieMoveMovie->start();
    }
    if(isToVault == true)//遇到第一个植物，跳跃
    {
        mediaPlayer_zoobieVaulting->play();
        this->setMovie(zoobieVaultingMovie);
        zoobieVaultingMovie->start();
    }
    if(hasVaulted == true && isEatingPlants == false && isToVault == false)//跳过第一个植物后，正常走路时
    {
        this->setMovie(vaultingZoobieWalkMovie);
        vaultingZoobieWalkMovie->start();
    }
    if(hasVaulted == true && isEatingPlants == true && isToVault == false)//跳过第一个植物后，吃东西时
    {
        mediaPlayer_zoobieEating->play();
        this->setMovie(zoobieEatingMovie);
        zoobieEatingMovie->start();
    }
}
