#ifndef POLEVAULTINGZOOBIE_H
#define POLEVAULTINGZOOBIE_H
//雪橇僵尸

#include "zoobie.h"

class PoleVaultingZoobie:public Zoobie
{
    Q_OBJECT
public:

    explicit PoleVaultingZoobie(QWidget* parent=0);
    bool isToVault{false};//是否将要撑杆跳
    bool hasVaulted{false};//是否已经跳过了
    QMovie *zoobieVaultingMovie;//跳的动作
    QMovie *vaultingZoobieWalkMovie;//跳完以后走路的动作
    QMediaPlayer *mediaPlayer_zoobieVaulting;//撑杆跳的声音

public slots:
    void slot_zoobieActionChange();//重写动作改变函数
    void slot_zoobiePositionChange();//重写位置移动函数
    void slot_changePoleVaultingZoobieFlag();//改变flag
};

#endif // POLEVAULTINGZOOBIE_H
