#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

#include "QVector"

#include "pea.h"
#include "shovel.h"
#include "sunflower.h"
#include "wallnut.h"
#include "sunshine.h"
#include "lawncleaner.h"

#include "zoobie.h"
#include "bucketzoobie.h"
#include "polevaultingzoobie.h"

#include "QLineEdit"
#include "QPushButton"
#include "QImage"
#include "QTimer"
#include "QMediaPlayer"
#include "QMediaPlaylist"

#include "cmath"
#include "ctime"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void scrollBackgroundImage();

    //游戏音乐的设置
    QMediaPlayer *mediaPlayer_gameWindowBackground;//背景音乐
    QMediaPlaylist *mediaPlaylist_gameWindowBackground;
    QMediaPlayer *mediaPlayer_bulletHitZoobie;//子弹打到僵尸
    QMediaPlayer *mediaPlayer_bulletHitBucketZoobie;//子弹打到铁桶僵尸
    QMediaPlayer *mediaPlayer_gameWin;//游戏胜利的音效
    QMediaPlayer *mediaPlayer_gameLose;//游戏失败的音效
    QMediaPlayer *mediaPlayer_siren;//警报声
    QMediaPlayer *mediaPlayer_buttonClicked;//点击按钮声
    QMediaPlayer *mediaPlayer_shovel;//铲子铲植物

    Pea *peaArray[5][9];//存储Pea的Array
    SunFlower *sunFlowerArray[5][9];//存储SunFlower的Array
    WallNut *wallNutArray[5][9]; //存储WallNut的Array
    LawnCleaner *lawnCleanerArray[5];//存储lawncleaner的array

    QList<Zoobie*> zoobieList;//存储普通僵尸的List
    QList<BucketZoobie*> bucketZoobieList;//存储铁桶僵尸的List
    QList<PoleVaultingZoobie*> poleVaultingZoobieList;//存储撑杆跳僵尸的List

    int zoobieRound{1};//普通僵尸轮数计数器
    int bucketZoobieRound{1};//铁桶僵尸轮数计数器
    int poleVaultingZoobieRound{1};//撑杆跳僵尸轮数计数器

    int zoobieRoundUpperLimit{5};//普通僵尸轮数上限
    int bucketZoobieRoundUpperLimit{5};//铁桶僵尸轮数上限
    int poleVaultingZoobieRoundUpperLimit{5};//撑杆跳僵尸轮数上限

    int numOfBImgRightMove{0};
    int numOfBImgLeftMove{0};
    int temp_leftPeaCoolingTime{7500};//倒计时用的剩余冷却时间
    int temp_leftWallNutCoolingTime{30000};
    int temp_leftSunFlowerCoolingTime{7500};
    const int autoSunshineFallingSpeed{1};//主界面美秒刷新50下，每次刷新走2个像素点

    int autoSunshineFallingPosY{0};//自动阳光实时Y坐标
    int autoSunshineDestinationPosX{0};//自动阳光的每一次最终X坐标，也是实时X坐标
    int autoSunshineDestinationPosY{0};//自动阳光每一次的最终Y坐标

    int autoSunshineInterval{20000};//自然阳光的产生间隔
    int zoobieProduceInterval{15000};//普通僵尸产生间隔
    int bucketZoobieProduceInterval{15000};//铁桶僵尸产生间隔
    int PoleVaultingZoobieProduceInterval{15000};//撑杆跳僵尸产生间隔

    QLabel *myBackGroundLabel;//背景label

    QLabel *shovelHolder;//铲子后面的label
    QLabel *sunshineHolder;//阳光后面的label
    QLabel *cardHolder;//卡片栏label

    QLabel *gameWinLabel;//游戏胜利时显示用的label
    QImage *gameWinImg;//游戏胜利时的图像
    QLabel *gameLoseLabel;//游戏失败时显示用的label
    QImage *gameLoseImg;//游戏失败时的图像

    QPushButton *sunFlowerPushButton;
    QPushButton *peaPushButton;
    QPushButton *wallNutPushButton;
    QPushButton *shovelPushButton;

    QImage *backGroundImg;
    QImage *shovelHolderImg;//铲子后面的label对应的图片
    QImage *sunshineHolderImg;//阳光后面的label的图片
    QImage *cardHolderImg;//卡片栏label的图片

    QLineEdit *sunshineLineEdit;
    QLineEdit *peaCoolingDownLineEdit;
    QLineEdit *wallNutCoolingDownLineEdit;
    QLineEdit *sunFlowerCoolingDownLineEdit;

    bool isFieldPlantable[5][9];//每块地能否种植物的bool数组
    int hasFieldPlanted[5][9];//0是没种植物，1是向日葵，2是普通豌豆射手，3是坚果
    bool isSettingPea{false};
    bool ableToSetPea{false};//防止鼠标随便点就种植物
    bool isSettingWallNut{false};
    bool ableToSetWallNut{false};//防止鼠标随便点就种植物
    bool isSettingSunFlower{false};
    bool ableToSetSunFlower{false};//防止鼠标随便点就种植物
    bool isToShovelPlants{false};
    bool ableToShovelPlants{false};//防止鼠标随便点就铲植物
    bool isPeaCooling{false};
    bool isWallNutCooling{false};
    bool isSunFlowerCooling{false};//记录植物是否处于冷却时间里

    QTimer *gameWindowTimer;
    QTimer *peaCoolingDownTimer;
    QTimer *sunFlowerCoolingDownTimer;
    QTimer *wallNutCoolingDownTimer;
    QTimer *autoSunshineTimer;//自然阳光产生的计时器
    QTimer *autoSunshineTimerRefresher;
    //和僵尸有关的QTimer
    QTimer *zoobieProduceTimer;
    QTimer *bucketZoobieProduceTimer;
    QTimer *poleVaultingZoobieProduceTimer;

    SunShine *autoSunshine;

    void func_gameLose();//游戏失败的时候显示动画，结束计时器
    void func_gameWin();

public slots:
    void slot_showBackgroundImage();
    void slot_clickPeaPushButton();
    void slot_clickWallNutPushButton();
    void slot_clickSunFlowerPushButton();
    void slot_clickShovelPushButton();
    void slot_refreshSunshineLineEdit();
    void slot_setPeaPushButtonAbled();
    void slot_setWallNutPushButtonAbled();
    void slot_setSunFlowerPushButtonAbled();
    void slot_sunFlowerCountDown();
    void slot_peaCountDown();
    void slot_wallNutCountDown();
    void slot_produceAutoSunshine();
    void slot_autoSunshinePosRefresh();
    void slot_setAutoSunshinePos();
    void slot_raiseCardButton();

    //与僵尸有关的slot
    void slot_produceZoobie();//生成普通僵尸
    void slot_produceBucketZoobie();//生成铁桶僵尸
    void slot_producePoleVaultingZoobie();//生产撑杆跳僵尸
    void slot_change_P_and_Z_state();//每一帧修改植物和僵尸的状态
    void slot_deleteDeadPlant();//删除死亡植物
    void slot_checkBulletHitZoobie();//检查子弹是否命中
    void slot_deleteDeadZoobie();//删除死亡僵尸
    void slot_deleteOutOfRangeBullet();//删除飞出屏幕外的子弹

    //与游戏进程有关的slot
    void slot_checkGameLose();
    void slot_checkGameWin();
    void slot_stopAllTimer();

    void slot_LawnCleanerInitial();//小车初始化
    void slot_LawnCleanerActivate();//小车激活
    void slot_LawnCleanerAttack();//小车攻击
    void slot_deleteOutOfRangeLawnCleaner();//删除小车

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::GameWindow *ui;

};

#endif // GAMEWINDOW_H
