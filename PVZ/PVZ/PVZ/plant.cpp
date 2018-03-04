#include "plant.h"


Plant::Plant(QWidget* parent):QLabel(parent)
{
    //种植植物的声音
    mediaPlayer_plant = new QMediaPlayer(this);
    mediaPlayer_plant->setMedia(QUrl("qrc:/new/music/plant1.mp3"));
    mediaPlayer_plant->setVolume(150);
    mediaPlayer_plant->play();
}

