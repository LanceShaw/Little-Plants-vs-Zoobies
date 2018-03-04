#include "gamewindow.h"
#include "ui_gamewindow.h"

#include"globalvariable.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    //UI的建立
    ui->setupUi(this);

    //随机数种子的生成
    srand(time(0));

    //游戏主计时器的初始化
    gameWindowTimer = new QTimer(this);
    gameWindowTimer->setInterval(20);//每秒屏幕刷新50次
    gameWindowTimer->start();

    //游戏背景音乐的设置
    mediaPlayer_gameWindowBackground = new QMediaPlayer(this);
    mediaPlaylist_gameWindowBackground = new QMediaPlaylist(this);
    mediaPlaylist_gameWindowBackground->addMedia(QUrl("qrc:/new/music/UraniwaNi.mp3"));
    mediaPlaylist_gameWindowBackground->setCurrentIndex(1);
    mediaPlaylist_gameWindowBackground->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaPlayer_gameWindowBackground->setPlaylist(mediaPlaylist_gameWindowBackground);
    mediaPlayer_gameWindowBackground->setVolume(150);
    mediaPlayer_gameWindowBackground->play();

    //点击按钮声音
    mediaPlayer_buttonClicked = new QMediaPlayer(this);
    mediaPlayer_buttonClicked->setMedia(QUrl("qrc:/new/music/buttonclick.mp3"));
    mediaPlayer_buttonClicked->setVolume(150);

    //子弹打到普通僵尸的音乐
    mediaPlayer_bulletHitZoobie = new QMediaPlayer(this);
    mediaPlayer_bulletHitZoobie->setMedia(QUrl("qrc:/new/music/splat1.mp3"));
    mediaPlayer_bulletHitZoobie->setVolume(150);

    //子弹打到铁桶僵尸的音乐
    mediaPlayer_bulletHitBucketZoobie = new QMediaPlayer(this);
    mediaPlayer_bulletHitBucketZoobie->setMedia(QUrl("qrc:/new/music/shieldhit.mp3"));
    mediaPlayer_bulletHitBucketZoobie->setVolume(150);

    //游戏胜利的音效
    mediaPlayer_gameWin = new QMediaPlayer(this);
    mediaPlayer_gameWin->setMedia(QUrl("qrc:/new/music/winmusic.mp3"));
    mediaPlayer_gameWin->setVolume(150);

    //游戏失败的音效
    mediaPlayer_gameLose = new QMediaPlayer(this);
    mediaPlayer_gameLose->setMedia(QUrl("qrc:/new/music/scream.mp3"));
    mediaPlayer_gameLose->setVolume(150);

    //警报声的音效
    mediaPlayer_siren = new QMediaPlayer(this);
    mediaPlayer_siren->setMedia(QUrl("qrc:/new/music/siren.mp3"));
    mediaPlayer_siren->setVolume(150);

    //铲子铲植物
    mediaPlayer_shovel = new QMediaPlayer(this);
    mediaPlayer_shovel->setMedia(QUrl("qrc:/new/music/shovel.mp3"));
    mediaPlayer_shovel->setVolume(150);

    //背景label相关设置
    myBackGroundLabel = new QLabel(ui->centralwidget);
    backGroundImg = new QImage(":/new/gamaWindow/background1.png");
    myBackGroundLabel->setGeometry(0,0,900,600);
    myBackGroundLabel->setScaledContents(true);
    myBackGroundLabel->setPixmap(QPixmap::fromImage(*backGroundImg));
    this->scrollBackgroundImage();//开始场景混动

    //小推车的初始化
    for(int i=0; i<5;i++)
    {
        lawnCleanerArray[i] = nullptr;
    }
    gameWindowTimer->singleShot(5000,this,SLOT(slot_LawnCleanerInitial()));

    //铲子拦相关设置
    shovelHolder = new QLabel(ui->centralwidget);
    shovelHolder->setGeometry(380,10,111,41);
    shovelHolder->setScaledContents(true);
    shovelHolderImg = new QImage(":/new/Shovel/ShovelBack.png");
    shovelHolder->setPixmap(QPixmap::fromImage(*shovelHolderImg));

      //阳关拦相关设置
    sunshineHolder = new QLabel(ui->centralwidget);
    sunshineHolder->setGeometry(190,10,100,41);
    sunshineHolder->setScaledContents(true);
    sunshineHolderImg = new QImage(":/new/Sunshine/SunBack.png");
    sunshineHolder->setPixmap(QPixmap::fromImage(*sunshineHolderImg));

    //卡片栏相关设置
    cardHolder = new QLabel(ui->centralwidget);
    cardHolder->setGeometry(10,10,105,500);
    cardHolder->setScaledContents(true);
    cardHolderImg = new QImage(":/new/gamaWindow/SeedChooser_Background.png");
    cardHolder->setPixmap(QPixmap::fromImage(*cardHolderImg));

    //向日葵卡片的设置
    sunFlowerPushButton = new QPushButton(ui->centralwidget);
    sunFlowerPushButton->setGeometry(12,40,99,54);
    sunFlowerPushButton->setIcon(QIcon(":/new/SunFlower/SunFlowerECard.png"));
    sunFlowerPushButton->setIconSize(QSize(99,54));

    //向日葵冷却倒计时栏的设置
    sunFlowerCoolingDownLineEdit = new QLineEdit(ui->centralwidget);
    sunFlowerCoolingDownLineEdit->hide();
    sunFlowerCoolingDownLineEdit->setGeometry(12,40,99,54);
    sunFlowerCoolingDownLineEdit->setReadOnly(true);
    sunFlowerCoolingDownLineEdit->setFont(QFont(".SF NS Text",20));
    sunFlowerCoolingDownLineEdit->setAlignment(Qt::AlignCenter);
    sunFlowerCoolingDownLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");//将sunLineEdit设置为透明背景

    //豌豆卡片的设置
    peaPushButton = new QPushButton(ui->centralwidget);
    peaPushButton->setGeometry(10,100,99,54);
    peaPushButton->setIcon(QIcon(":/new/Pea/PeashooterECard.png"));
    peaPushButton->setIconSize(QSize(99,54));

    //豌豆冷却倒计时栏的设置
    peaCoolingDownLineEdit = new QLineEdit(ui->centralwidget);
    peaCoolingDownLineEdit->hide();
    peaCoolingDownLineEdit->setGeometry(10,100,99,54);
    peaCoolingDownLineEdit->setReadOnly(true);
    peaCoolingDownLineEdit->setFont(QFont(".SF NS Text",20));
    peaCoolingDownLineEdit->setAlignment(Qt::AlignCenter);
    peaCoolingDownLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");//将sunLineEdit设置为透明背景

    //坚果卡片的设置
    wallNutPushButton = new QPushButton(ui->centralwidget);
    wallNutPushButton->setGeometry(10,160,99,54);
    wallNutPushButton->setIcon(QIcon(":/new/WallNut/WallNutECard.png"));
    wallNutPushButton->setIconSize(QSize(99,54));

    //坚果冷却倒计时栏的设置
    wallNutCoolingDownLineEdit = new QLineEdit(ui->centralwidget);
    wallNutCoolingDownLineEdit ->hide();
    wallNutCoolingDownLineEdit ->setGeometry(10,160,99,54);
    wallNutCoolingDownLineEdit ->setReadOnly(true);
    wallNutCoolingDownLineEdit ->setFont(QFont(".SF NS Text",20));
    wallNutCoolingDownLineEdit ->setAlignment(Qt::AlignCenter);
    wallNutCoolingDownLineEdit ->setStyleSheet("background:transparent;border-width:0;border-style:outset");//将sunLineEdit设置为透明背景


    //铲子卡片的设置
    shovelPushButton = new QPushButton(ui->centralwidget);
    shovelPushButton->setGeometry(380,10,111,41);
    shovelPushButton->setIcon(QIcon(":/new/Shovel/Shovel.png"));
    shovelPushButton->setIconSize(QSize(111,41));
    shovelPushButton->setFlat(true);//去除边框

    //阳光文本框的实现
    sunshineLineEdit = new QLineEdit(ui->centralwidget);
    sunshineLineEdit->setGeometry(220,10,100,41);
    sunshineLineEdit->setReadOnly(true);
    sunshineLineEdit->setFont(QFont(".SF NS Text",30));

    //二维bool数组初始化
    memset(isFieldPlantable,true,sizeof(isFieldPlantable));
    memset(hasFieldPlanted,0,sizeof(hasFieldPlanted));

    //三个植物数组的初始化；
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            peaArray[i][j] = nullptr;
        }
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            sunFlowerArray[i][j] = nullptr;
        }
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            wallNutArray[i][j] = nullptr;
        }
    }

    //各个button相关的连接
    QObject::connect(peaPushButton,SIGNAL(clicked()),this,SLOT(slot_clickPeaPushButton()));
    QObject::connect(sunFlowerPushButton,SIGNAL(clicked()),this,SLOT(slot_clickSunFlowerPushButton()));
    QObject::connect(wallNutPushButton,SIGNAL(clicked()),this,SLOT(slot_clickWallNutPushButton()));
    QObject::connect(shovelPushButton,SIGNAL(clicked()),this,SLOT(slot_clickShovelPushButton()));

    //与小车有关的连接
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_LawnCleanerActivate()));
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_LawnCleanerAttack()));
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_deleteOutOfRangeLawnCleaner()));

    //和阳光有关的连接
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_refreshSunshineLineEdit()));//刷新阳光值的显示
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_raiseCardButton()));//时刻让卡片栏及卡片处于最顶层
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_autoSunshinePosRefresh()));//自动更新自然阳光的位置

    //与阳光有关的初始化及设置
    autoSunshineTimerRefresher = new QTimer(this);
    autoSunshineTimerRefresher->setInterval(20);

    autoSunshine = new SunShine(ui->centralwidget);
    autoSunshine->setGeometry(1000,0,82,100);//把第一个阳光移走
    autoSunshineTimer = new QTimer(this);
    autoSunshineTimer->setInterval(autoSunshineInterval);//阳光20秒掉一个
    autoSunshineTimer->start();
    QObject::connect(autoSunshineTimer,SIGNAL(timeout()),this,SLOT(slot_produceAutoSunshine()));

    //与僵尸有关的初始化及设置
    //普通僵尸生产计时器及僵尸产生
    zoobieProduceTimer = new QTimer(this);
    zoobieProduceTimer->setInterval(zoobieProduceInterval);
    zoobieProduceTimer->start();
    QObject::connect(zoobieProduceTimer,SIGNAL(timeout()),this,SLOT(slot_produceZoobie()));

    //铁桶僵尸生产计时器及僵尸产生
    bucketZoobieProduceTimer = new QTimer(this);
    bucketZoobieProduceTimer->setInterval(bucketZoobieProduceInterval);
    bucketZoobieProduceTimer->start();
    QObject::connect(bucketZoobieProduceTimer,SIGNAL(timeout()),this,SLOT(slot_produceBucketZoobie()));

    //撑杆跳僵尸生产计时器及僵尸产生
    poleVaultingZoobieProduceTimer = new QTimer(this);
    poleVaultingZoobieProduceTimer->setInterval(PoleVaultingZoobieProduceInterval);
    poleVaultingZoobieProduceTimer->start();
    QObject::connect(poleVaultingZoobieProduceTimer,SIGNAL(timeout()),this,SLOT(slot_producePoleVaultingZoobie()));

    //僵尸和植物交互的几个connect
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_change_P_and_Z_state()));//改变僵尸和植物的状态
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_deleteDeadPlant()));//删掉已经死的植物
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_checkBulletHitZoobie()));//检查子弹是否命中僵尸
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_deleteDeadZoobie()));//删除已经死掉的僵尸
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_deleteOutOfRangeBullet()));//删除飞出屏幕外的子弹

    //游戏结束的几个label的设置
    //游戏胜利的设置
    gameWinLabel = new QLabel(ui->centralwidget);
    gameWinLabel->setScaledContents(true);
    gameWinImg = new QImage(":/new/GameEnd/trophy.png");
    gameWinLabel->setPixmap(QPixmap::fromImage(*gameWinImg));
    gameWinLabel->hide();
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_checkGameWin()));

    //游戏失败的设置
    gameLoseLabel = new QLabel(ui->centralwidget);
    gameLoseLabel->setScaledContents(true);
    gameLoseImg = new QImage(":/new/GameEnd/ZombiesWon.png");
    gameLoseLabel->setPixmap(QPixmap::fromImage(*gameLoseImg));
    gameLoseLabel->hide();
    QObject::connect(gameWindowTimer,SIGNAL(timeout()),this,SLOT(slot_checkGameLose()));

}

//删除小车
void GameWindow::slot_deleteOutOfRangeLawnCleaner()
{
    for(int i=0; i<5; i++)
    {
        if(lawnCleanerArray[i] != nullptr)
        {
            if(lawnCleanerArray[i]->pos().x() >= 900)
            {
                if(lawnCleanerArray[i]->isRunning == true)
                {
                    delete lawnCleanerArray[i];
                    lawnCleanerArray[i] = nullptr;
                }
            }
        }
    }
}

//小车攻击
void GameWindow::slot_LawnCleanerAttack()
{
    for(int i=0; i<5; i++)
    {
        if(lawnCleanerArray[i] != nullptr)
        {
            if(lawnCleanerArray[i]->isActivited == true && lawnCleanerArray[i]->isRunning == true)//被激活
            {

                //遍历普通僵尸
                for( int z=0; z < zoobieList.size(); z++)
                {
                    if(std::abs(lawnCleanerArray[i]->pos().x() - zoobieList[z]->posX )<= 10 && i == zoobieList[z]->row)//x坐标小于10
                    {
                        zoobieList[z]->life = zoobieList[z]->life - lawnCleanerArray[i]->damage;
                    }
                }

                //铁桶僵尸
                for( int bZ = 0; bZ < bucketZoobieList.size() ; bZ++)
                {
                    if(std::abs(lawnCleanerArray[i]->pos().x() - bucketZoobieList[bZ]->posX )<= 10 && i == bucketZoobieList[bZ]->row)//x坐标小于10
                    {
                        bucketZoobieList[bZ]->life = bucketZoobieList[bZ]->life - lawnCleanerArray[i]->damage;
                    }
                }

                //撑杆跳僵尸
                for( int pvZ = 0; pvZ < poleVaultingZoobieList.size() ; pvZ++)
                {
                    if(std::abs(lawnCleanerArray[i]->pos().x()-82-50 - poleVaultingZoobieList[pvZ]->posX )<= 10 && i == poleVaultingZoobieList[pvZ]->row)//x坐标小于10
                    {
                        poleVaultingZoobieList[pvZ]->life = poleVaultingZoobieList[pvZ]->life - lawnCleanerArray[i]->damage;
                    }
                }
            }
        }
    }
}

//小车激活
void GameWindow::slot_LawnCleanerActivate()
{
    for(int i=0; i<5; i++)
    {
        if(lawnCleanerArray[i] != nullptr)
        {
            if(lawnCleanerArray[i]->isActivited == false && lawnCleanerArray[i]->isRunning == false)//还没被激活
            {
                //普通僵尸
                for( int z = 0; z < zoobieList.size() ; z++)
                {
                    if(std::abs(lawnCleanerArray[i]->pos().x() - zoobieList[z]->posX )<= 20 && i == zoobieList[z]->row)//x坐标小于20
                    {
                        lawnCleanerArray[i]->isActivited = true;
                        return;
                    }
                }

                //铁桶僵尸
                for( int bZ = 0; bZ < bucketZoobieList.size() ; bZ++)
                {
                    if(std::abs(lawnCleanerArray[i]->pos().x() - bucketZoobieList[bZ]->posX )<= 20 && i == bucketZoobieList[bZ]->row)//x坐标小于20
                    {
                        lawnCleanerArray[i]->isActivited = true;
                        return;
                    }
                }

                //撑杆跳僵尸
                for( int pvZ = 0; pvZ < poleVaultingZoobieList.size() ; pvZ++)
                {
                    if(std::abs(lawnCleanerArray[i]->pos().x()-82-50 - poleVaultingZoobieList[pvZ]->posX )<= 20 && i == poleVaultingZoobieList[pvZ]->row)//x坐标小于20
                    {
                        lawnCleanerArray[i]->isActivited = true;
                        return;
                    }
                }

            }
        }
    }
}

//小推车初始化
void GameWindow::slot_LawnCleanerInitial()
{
    //播放音效
    mediaPlayer_siren->play();
    //初始化
    for(int row=0 ; row<5 ; row++)
    {
        lawnCleanerArray[row] = new LawnCleaner(ui->centralwidget);
        lawnCleanerArray[row]->hide();
        lawnCleanerArray[row]->row = row;
        lawnCleanerArray[row]->slot_enter();
    }

}

//让所有timer停止
void GameWindow::slot_stopAllTimer()
{
    //游戏主窗口QTimer停止
    gameWindowTimer->stop();
    //自动产阳光的QTimer停止
    autoSunshineTimer->stop();

    //向日葵和豌豆射手timer的停止
    for(int row=0; row<5; row++)
    {
        for(int col=0; col <9;col++)
        {
            if(peaArray[row][col] != nullptr)
            {
                peaArray[row][col]->shootingTriggerTimer->stop();
            }
            if(sunFlowerArray[row][col] != nullptr)
            {
                sunFlowerArray[row][col]->sunFlowerSunshineTimer->stop();
            }
        }
    }

    //各个僵尸的timer的停止
    //普通僵尸
    QList<Zoobie*>::iterator z;
    for( z = zoobieList.begin(); z != zoobieList.end() ; z++)
    {
        (*z)->zoobieTimer->stop();
    }

    //铁桶僵尸
    QList<BucketZoobie*>::iterator bZ;
    for( bZ = bucketZoobieList.begin(); bZ != bucketZoobieList.end() ; bZ++)
    {
        (*bZ)->zoobieTimer->stop();
    }

    //撑杆跳僵尸
    QList<PoleVaultingZoobie*>::iterator pvZ;
    for( pvZ = poleVaultingZoobieList.begin(); pvZ != poleVaultingZoobieList.end() ; pvZ++)
    {
        (*pvZ)->zoobieTimer->stop();
    }

}

//游戏胜利时动画与音效
void GameWindow::func_gameWin()
{
    gameWinLabel->show();
    gameWinLabel->raise();
    QPropertyAnimation *tempAnimation;
    tempAnimation = new QPropertyAnimation(gameWinLabel,"geometry");
    tempAnimation->setDuration(5000);
    tempAnimation->setStartValue(QRect(450,300,0,0));
    tempAnimation->setEndValue(QRect(250,80,500,440));
    tempAnimation->start();
    mediaPlayer_gameWin->play();
}

//检查游戏是否胜利
void GameWindow::slot_checkGameWin()
{
    if(zoobieRound >= zoobieRoundUpperLimit && bucketZoobieRound >= bucketZoobieRoundUpperLimit && poleVaultingZoobieRound >= poleVaultingZoobieRoundUpperLimit)//游戏必须进行到规定的轮次
    {
        if(zoobieList.isEmpty() == true && bucketZoobieList.isEmpty() == true && poleVaultingZoobieList.isEmpty() == true)//没有僵尸了
        {
            slot_stopAllTimer();
            func_gameWin();
            return;
        }
    }
}

//游戏失败时动画与音效
void GameWindow::func_gameLose()
{
    gameLoseLabel->show();
    gameLoseLabel->raise();
    QPropertyAnimation *tempAnimation;
    tempAnimation = new QPropertyAnimation(gameLoseLabel,"geometry");
    tempAnimation->setDuration(5000);
    tempAnimation->setStartValue(QRect(450,300,0,0));
    tempAnimation->setEndValue(QRect(250,80,500,440));
    tempAnimation->start();
    mediaPlayer_gameLose->play();

}

//检查游戏是否失败
void GameWindow::slot_checkGameLose()
{
    //普通僵尸
    for( int z = 0; z < zoobieList.size() ; z++)
    {
        if(zoobieList[z]->posX <= 10)//x坐标小于10
        {
            slot_stopAllTimer();
            func_gameLose();
            return;
        }
    }

    //铁桶僵尸
    for( int bZ = 0; bZ < bucketZoobieList.size();  bZ++)
    {
        if(bucketZoobieList[bZ]->posX <= 10)//x坐标小于10
        {
            slot_stopAllTimer();
            func_gameLose();
            return;
        }
    }

    //撑杆跳僵尸
    for( int pvZ = 0; pvZ < poleVaultingZoobieList.size() ; pvZ++)
    {
        if(poleVaultingZoobieList[pvZ]->posX <= -150)//x坐标小于10
        {
            slot_stopAllTimer();
            func_gameLose();
            return;
        }
    }
}

//删除飞出屏幕外的子弹
void GameWindow::slot_deleteOutOfRangeBullet()
{
    for(int row = 0; row < 5; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            if(hasFieldPlanted[row][col] == 2)
            {

                for(int b = 0; b < peaArray[row][col]->bulletList.size(); b++)//对每一颗子弹遍历
                {

                        if(peaArray[row][col]->bulletList[b]->pos().x() >= 900)//在屏幕外
                        {
                            delete peaArray[row][col]->bulletList[b];
                            peaArray[row][col]->bulletList.removeAt(b);//删除这个子弹
                        }

                }
            }
        }
    }
}

//删除死亡僵尸
void GameWindow::slot_deleteDeadZoobie()
{

    //遍历普通僵尸
    for(int z=0;z<zoobieList.size();z++)
    {
        if(zoobieList[z]->life <= 0)//如果血少于0
        {
                 //修改这一行豌豆的状态
             for(int col = 0; col < 9; col++)
             {
                 if(hasFieldPlanted[zoobieList[z]->row][col] == 2)//是豌豆的话
                 {
                        peaArray[zoobieList[z]->row][col]->isAttacking = false;
                  }
              }
              delete zoobieList[z];
              zoobieList.removeAt(z);
        }
    }

    //遍历铁桶僵尸
    for(int z=0;z<bucketZoobieList.size();z++)
    {
        if(bucketZoobieList[z]->life <= 0)//如果血少于0
        {
                 //修改这一行豌豆的状态
             for(int col = 0; col < 9; col++)
             {
                 if(hasFieldPlanted[bucketZoobieList[z]->row][col] == 2)//是豌豆的话
                 {
                        peaArray[bucketZoobieList[z]->row][col]->isAttacking = false;
                  }
              }
              delete bucketZoobieList[z];
              bucketZoobieList.removeAt(z);
        }
    }

    //遍历撑杆跳僵尸
    for(int z=0;z<poleVaultingZoobieList.size();z++)
    {
        if(poleVaultingZoobieList[z]->life <= 0)//如果血少于0
        {
                 //修改这一行豌豆的状态
             for(int col = 0; col < 9; col++)
             {
                 if(hasFieldPlanted[poleVaultingZoobieList[z]->row][col] == 2)//是豌豆的话
                 {
                        peaArray[poleVaultingZoobieList[z]->row][col]->isAttacking = false;
                  }
              }
              delete poleVaultingZoobieList[z];
              poleVaultingZoobieList.removeAt(z);
        }
    }

}

//检查子弹是否命中僵尸
void GameWindow::slot_checkBulletHitZoobie()
{
    for(int row=0;row<5;row++)
    {
        for(int col=0;col<9;col++)
        {
            if(hasFieldPlanted[row][col] == 2)//如果是豌豆的话
            {
                if(peaArray[row][col]->isAttacking == true)//处于攻击状态
                {

                    for(int b = 0; b < peaArray[row][col]->bulletList.size(); b++)//对每一颗子弹遍历
                    {

                            for(int z = 0; z < zoobieList.size() ; z++)//对普通僵尸遍历
                            {
                                if(row == zoobieList[z]->row &&  peaArray[row][col]->bulletList[b]->pos().x() > zoobieList[z]->posX  )//在同一行并且x距离小于10
                                {
                                    mediaPlayer_bulletHitZoobie->play();
                                    zoobieList[z]->life = zoobieList[z]->life - peaArray[row][col]->bulletList[b]->damage;//对僵尸造成伤害
                                    peaArray[row][col]->bulletList[b]->bulletExplode();
                                    peaArray[row][col]->bulletList.removeAt(b);//删除这个子弹
                                    --b;//保证子弹不会miss掉
                                    break;//跳出
                                }
                            }

                    }

                    for(int b = 0; b < peaArray[row][col]->bulletList.size(); b++)//对每一颗子弹遍历
                    {

                            for(int bZ = 0; bZ < bucketZoobieList.size(); bZ++)//对铁桶僵尸遍历
                            {
                                if(row == bucketZoobieList[bZ]->row &&  peaArray[row][col]->bulletList[b]->pos().x() > bucketZoobieList[bZ]->posX )//在同一行并且x距离小于10
                                {
                                    mediaPlayer_bulletHitBucketZoobie->play();
                                    bucketZoobieList[bZ]->life = bucketZoobieList[bZ]->life - peaArray[row][col]->bulletList[b]->damage;//对僵尸造成伤害
                                    peaArray[row][col]->bulletList[b]->bulletExplode();
                                    peaArray[row][col]->bulletList.removeAt(b);//删除这个子弹
                                    --b;//保证子弹不会miss掉
                                    break;//跳出
                                }
                            }

                    }

                    for(int b = 0; b < peaArray[row][col]->bulletList.size(); b++)//对每一颗子弹遍历
                    {

                            for(int pvZ = 0; pvZ < poleVaultingZoobieList.size(); pvZ++)//对铁桶僵尸遍历
                            {
                                if(row == poleVaultingZoobieList[pvZ]->row &&  peaArray[row][col]->bulletList[b]->pos().x()-82-100 > poleVaultingZoobieList[pvZ]->posX  )//在同一行并且x距离小于10
                                {
                                    mediaPlayer_bulletHitZoobie->play();
                                    poleVaultingZoobieList[pvZ]->life = poleVaultingZoobieList[pvZ]->life - peaArray[row][col]->bulletList[b]->damage;//对僵尸造成伤害
                                    peaArray[row][col]->bulletList[b]->bulletExplode();
                                    peaArray[row][col]->bulletList.removeAt(b);//删除这个子弹
                                    --b;//保证子弹不会miss掉
                                    break;//跳出
                                }
                            }

                    }

                }
            }
        }
    }
}

//删除死亡的植物
void GameWindow::slot_deleteDeadPlant()
{
    for(int row=0;row<5;row++)
    {
        for(int col=0;col<9;col++)
        {
            if(hasFieldPlanted[row][col]>0)//如果种植物的话
            {
                switch(hasFieldPlanted[row][col])//修改植物的状态
                {
                    case 1:
                        if(sunFlowerArray[row][col]->life <= 0)//向日葵死了
                        {
                            for(int z = 0; z < zoobieList.size() ; z++)//对普通僵尸遍历
                            {
                                if(std::abs( 120 + col*82 + 55 - zoobieList[z]->posX) <= 10  && row == zoobieList[z]->row)//如果距离小于10
                                {
                                    zoobieList[z]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            for(int bZ = 0; bZ < bucketZoobieList.size() ; bZ++)//对铁桶僵尸遍历
                            {
                                if(std::abs( 120 + col*82 + 55- bucketZoobieList[bZ]->posX) <= 10 && row == bucketZoobieList[bZ]->row)//如果距离小于10
                                {
                                     bucketZoobieList[bZ]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            for(int pvZ = 0; pvZ < poleVaultingZoobieList.size(); pvZ++)//对撑杆跳僵尸遍历
                            {
                                if(std::abs( 120 + col*82 -100- poleVaultingZoobieList[pvZ]->posX) <= 10 && row == poleVaultingZoobieList[pvZ]->row)//如果距离小于10
                                {
                                     poleVaultingZoobieList[pvZ]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            delete sunFlowerArray[row][col];
                            sunFlowerArray[row][col] = nullptr;//删除一株向日葵并让其指向空指针
                            hasFieldPlanted[row][col] = 0;
                            isFieldPlantable[row][col] = true;//这块地又可以种植物了
                        }
                    break;
                    case 2:
                        if(peaArray[row][col]->life <= 0)
                        {

                            for(int z = 0; z < zoobieList.size() ; z++)//对普通僵尸遍历
                            {
                                if(std::abs( 120 + col*82 + 55 - zoobieList[z]->posX) <= 10  && row == zoobieList[z]->row)//如果距离小于10
                                {
                                    zoobieList[z]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            for(int bZ = 0; bZ < bucketZoobieList.size() ; bZ++)//对铁桶僵尸遍历
                            {
                                if(std::abs( 120 + col*82 + 55- bucketZoobieList[bZ]->posX) <= 10 && row == bucketZoobieList[bZ]->row)//如果距离小于10
                                {
                                     bucketZoobieList[bZ]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            for(int pvZ = 0; pvZ < poleVaultingZoobieList.size(); pvZ++)//对撑杆跳僵尸遍历
                            {
                                if(std::abs( 120 + col*82 -100- poleVaultingZoobieList[pvZ]->posX) <= 10 && row == poleVaultingZoobieList[pvZ]->row)//如果距离小于10
                                {
                                     poleVaultingZoobieList[pvZ]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            delete peaArray[row][col];
                            peaArray[row][col] = nullptr;//删除一株豌豆并让其指向空指针
                            hasFieldPlanted[row][col] = 0;
                            isFieldPlantable[row][col] = true;
                        }
                    break;
                    case 3:
                        if(wallNutArray[row][col]->life <= 0)
                        {

                            for(int z = 0; z < zoobieList.size() ; z++)//对普通僵尸遍历
                            {
                                if(std::abs( 120 + col*82 + 55 - zoobieList[z]->posX) <= 10  && row == zoobieList[z]->row)//如果距离小于10
                                {
                                    zoobieList[z]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            for(int bZ = 0; bZ < bucketZoobieList.size() ; bZ++)//对铁桶僵尸遍历
                            {
                                if(std::abs( 120 + col*82 + 55- bucketZoobieList[bZ]->posX) <= 10 && row == bucketZoobieList[bZ]->row)//如果距离小于10
                                {
                                     bucketZoobieList[bZ]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            for(int pvZ = 0; pvZ < poleVaultingZoobieList.size(); pvZ++)//对撑杆跳僵尸遍历
                            {
                                if(std::abs( 120 + col*82 -100- poleVaultingZoobieList[pvZ]->posX) <= 10 && row == poleVaultingZoobieList[pvZ]->row)//如果距离小于10
                                {
                                     poleVaultingZoobieList[pvZ]->isEatingPlants = false;//修改僵尸的状态
                                }
                            }

                            delete wallNutArray[row][col];
                            wallNutArray[row][col] = nullptr;//删除一个坚果并让其指向空指针
                            hasFieldPlanted[row][col] = 0;
                            isFieldPlantable[row][col] = true;
                        }
                    break;
                    default:
                    break;
                }
            }
        }
    }
}

//修改植物和僵尸的状态
void GameWindow::slot_change_P_and_Z_state()
{
    for(int row=0;row<5;row++)
    {
        for(int col=0;col<9;col++)
        {
            if(hasFieldPlanted[row][col] > 0)//从植物开始历遍,如果该位置有植物
            {
                //对普通僵尸遍历
                for(int z = 0; z < zoobieList.size() ; z++)
                {
                    if(zoobieList[z]->row == row && hasFieldPlanted[row][col] == 2)
                    {
                        peaArray[row][col]->isAttacking = true;//让这一行的豌豆射手攻击

                    }
                    if(std::abs( 120 + col*82 + 55 - zoobieList[z]->posX) <= 10  && row == zoobieList[z]->row)//如果距离小于10且在同一行
                    {
                        zoobieList[z]->isEatingPlants = true;//修改僵尸的状态
                        switch(hasFieldPlanted[row][col])//修改植物的状态
                        {
                            case 1:
                                sunFlowerArray[row][col]->life = sunFlowerArray[row][col]->life - 2;
                            break;
                            case 2:
                                peaArray[row][col]->life = peaArray[row][col]->life - 2;
                            break;
                            case 3:
                                wallNutArray[row][col]->life = wallNutArray[row][col]->life - 2;
                            break;
                            default:
                            break;
                        }
                     }

                }

                //对铁桶僵尸遍历
                for(int bZ = 0; bZ < bucketZoobieList.size() ; bZ++)
                {
                    if(bucketZoobieList[bZ]->row == row && hasFieldPlanted[row][col] == 2)
                    {
                        peaArray[row][col]->isAttacking = true;//让这一行的豌豆射手攻击
                    }
                    if(std::abs( 120 + col*82 + 55 - bucketZoobieList[bZ]->posX) <= 10 && row == bucketZoobieList[bZ]->row)//如果距离小于10且在同一行
                    {
                         bucketZoobieList[bZ]->isEatingPlants = true;//修改僵尸的状态
                        switch(hasFieldPlanted[row][col])//修改植物的状态
                        {
                            case 1:
                                sunFlowerArray[row][col]->life = sunFlowerArray[row][col]->life - 2;
                            break;
                            case 2:
                                peaArray[row][col]->life = peaArray[row][col]->life - 2;
                            break;
                            case 3:
                                wallNutArray[row][col]->life = wallNutArray[row][col]->life - 2;
                            break;
                            default:
                            break;
                        }
                     }
                }

                //对撑杆跳僵尸遍历
                for(int pvZ = 0; pvZ < poleVaultingZoobieList.size(); pvZ++)
                {
                    if(poleVaultingZoobieList[pvZ]->row == row && hasFieldPlanted[row][col] == 2)
                    {
                        peaArray[row][col]->isAttacking = true;//让这一行的豌豆射手攻击
                    }
                    if(std::abs( 120 + col*82 -100 - poleVaultingZoobieList[pvZ]->posX) <= 10 && row == poleVaultingZoobieList[pvZ]->row)//如果距离小于10且在同一行
                    {
                        if(poleVaultingZoobieList[pvZ]->isToVault == false && poleVaultingZoobieList[pvZ]->hasVaulted == false)
                        {
                            poleVaultingZoobieList[pvZ]->isToVault = true;
                            QObject::connect(poleVaultingZoobieList[pvZ]->zoobieVaultingMovie,SIGNAL(finished()),poleVaultingZoobieList[pvZ],SLOT(slot_changePoleVaultingZoobieFlag()));
                        }
                        if(poleVaultingZoobieList[pvZ]->hasVaulted == true)
                        {
                            poleVaultingZoobieList[pvZ]->isEatingPlants = true;//修改僵尸的状态
                           switch(hasFieldPlanted[row][col])//修改植物的状态
                           {
                               case 1:
                                   sunFlowerArray[row][col]->life = sunFlowerArray[row][col]->life - 2;
                               break;
                               case 2:
                                   peaArray[row][col]->life = peaArray[row][col]->life - 2;
                               break;
                               case 3:
                                   wallNutArray[row][col]->life = wallNutArray[row][col]->life - 2;
                               break;
                               default:
                               break;
                           }
                        }
                    }
                }

            }
        }
    }

}

//生产撑杆跳僵尸
void GameWindow::slot_producePoleVaultingZoobie()
{
    if(poleVaultingZoobieRound > (rand()%4) && poleVaultingZoobieRound <= poleVaultingZoobieRoundUpperLimit)
    {
        PoleVaultingZoobie *tempPoleVaultingZoobie = new PoleVaultingZoobie(ui->centralwidget);
        tempPoleVaultingZoobie->row = rand() % 5;
        tempPoleVaultingZoobie->posY = 80 + tempPoleVaultingZoobie->row*100.0 - 30;
        tempPoleVaultingZoobie->move(tempPoleVaultingZoobie->posX,tempPoleVaultingZoobie->posY);
        tempPoleVaultingZoobie->show();
        poleVaultingZoobieList << tempPoleVaultingZoobie;
    }
    poleVaultingZoobieRound++;
}

//生产铁桶僵尸及僵尸产生
void GameWindow::slot_produceBucketZoobie()
{
    if(bucketZoobieRound > (rand()%4) && bucketZoobieRound <= bucketZoobieRoundUpperLimit)
    {
        BucketZoobie *tempBucketZoobie = new BucketZoobie(ui->centralwidget);
        tempBucketZoobie->row = rand()%5;
        tempBucketZoobie->posY = 80.0 + tempBucketZoobie->row*100.0-30;
        tempBucketZoobie->move(tempBucketZoobie->posX,tempBucketZoobie->posY);
        tempBucketZoobie->show();
        bucketZoobieList << tempBucketZoobie;
    }
    bucketZoobieRound++;
}

//生产普通僵尸
void GameWindow::slot_produceZoobie()
{
    if(zoobieRound > (rand()%4) && zoobieRound <= zoobieRoundUpperLimit)
    {
        Zoobie *tempZoobie = new Zoobie(ui->centralwidget);
        tempZoobie->row = rand()%5;
        tempZoobie->posY = 80.0+ tempZoobie->row*100.0-30;
        tempZoobie->move(tempZoobie->posX,tempZoobie->posY);
        tempZoobie->show();
        zoobieList << tempZoobie;
    }
    zoobieRound++;
}

//让卡片栏处于最顶层
void GameWindow::slot_raiseCardButton()
{
    cardHolder->raise();
    sunFlowerPushButton->raise();
    sunFlowerCoolingDownLineEdit->raise();
    wallNutPushButton->raise();
    wallNutCoolingDownLineEdit->raise();
    peaPushButton->raise();
    peaCoolingDownLineEdit->raise();
}

//刷新自动阳光的位置
void GameWindow::slot_setAutoSunshinePos()
{
    if(autoSunshine->isCollected == false)
    {
        autoSunshine->raise();
        if(autoSunshineFallingPosY < autoSunshineDestinationPosY)
        {
            autoSunshine->setGeometry(autoSunshineDestinationPosX,autoSunshineFallingPosY,82,100);
        }
        else
        {
            autoSunshineFallingPosY = autoSunshineDestinationPosY;//稳定 autoSunshineFallingPosY 的值
            autoSunshine->setGeometry(autoSunshineDestinationPosX,autoSunshineDestinationPosY,82,100);
        }
    }
    else
        return;
}

//刷新自动产生的阳光的位置
void GameWindow::slot_autoSunshinePosRefresh()
{
    autoSunshineFallingPosY = autoSunshineFallingPosY + autoSunshineFallingSpeed;
}

//系统自动产生的阳光
void GameWindow::slot_produceAutoSunshine()
{
    autoSunshine->setGeometry(1000,0,82,100);
    autoSunshine->isCollected = false;//还没有收集自动阳光
    autoSunshineFallingPosY = 0;//初始掉落位置
    autoSunshineDestinationPosX = 120 + 82 * (rand()%9);
    autoSunshineDestinationPosY = 80 + 100 * (rand()%5);
    autoSunshineTimerRefresher->start();
    QObject::connect(autoSunshineTimerRefresher,SIGNAL(timeout()),this,SLOT(slot_setAutoSunshinePos()));//每隔20毫秒检查是否需要更新阳光位置
}

//向日葵冷却倒计时设计
void GameWindow::slot_sunFlowerCountDown()
{
    temp_leftSunFlowerCoolingTime = temp_leftSunFlowerCoolingTime - 50;
    int left_time = temp_leftSunFlowerCoolingTime / 1000;
    QString string_leftTime;
    string_leftTime = string_leftTime.setNum(left_time);//计算剩余时间，2位有效数字

   //lineEdit的相关设置
    sunFlowerCoolingDownLineEdit->setPlaceholderText(string_leftTime);//显示当前阳光值
    sunFlowerCoolingDownLineEdit->show();
}

//豌豆冷却倒计时设计
void GameWindow::slot_peaCountDown()
{
    temp_leftPeaCoolingTime = temp_leftPeaCoolingTime - 50;
    int left_time = temp_leftPeaCoolingTime / 1000;
    QString string_leftTime;
    string_leftTime = string_leftTime.setNum(left_time);//计算剩余时间，2位有效数字

   //lineEdit的相关设置
    peaCoolingDownLineEdit->setPlaceholderText(string_leftTime);//显示当前阳光值
    peaCoolingDownLineEdit->show();
}

//坚果冷却倒计时设计
void GameWindow::slot_wallNutCountDown()//坚果冷却倒计时设计
{
    temp_leftWallNutCoolingTime = temp_leftWallNutCoolingTime  - 50;
    int left_time = temp_leftWallNutCoolingTime  / 1000;
    QString string_leftTime;
    string_leftTime = string_leftTime.number(left_time);//计算剩余时间，2位有效数字

   //lineEdit的相关设置
    wallNutCoolingDownLineEdit->setPlaceholderText(string_leftTime);//显示当前阳光值
    wallNutCoolingDownLineEdit->show();
}

//解放向日葵卡片，修改冷却标志
void GameWindow::slot_setSunFlowerPushButtonAbled()
{
    sunFlowerPushButton->setDisabled(false);
    isSunFlowerCooling = false;
    sunFlowerCoolingDownLineEdit->hide();
}

//解放坚果卡片，修改冷却标志
void GameWindow::slot_setWallNutPushButtonAbled()
{
    wallNutPushButton->setDisabled(false);
    isWallNutCooling = false;
    wallNutCoolingDownLineEdit->hide();
}

//解放豌豆卡片，修改冷却标志
void GameWindow::slot_setPeaPushButtonAbled()
{
    peaPushButton->setDisabled(false);
    isPeaCooling = false;
    peaCoolingDownLineEdit->hide();
}

//刷新阳光值显示文本框
void GameWindow::slot_refreshSunshineLineEdit()
{
    QString stringNumOfSun;
    stringNumOfSun = stringNumOfSun.setNum(numOfSun);
    sunshineLineEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");//将sunLineEdit设置为透明背景
    sunshineLineEdit->setPlaceholderText(stringNumOfSun);//显示当前阳光值
}

//重写mousePressEvent函数,在屏幕上点击发生的事件
void GameWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)//必须是鼠标左键
    {
        int col = (event->pos().x() - 120) / 82;
        int row = (event->pos().y() - 80) / 100;
        if(col < 0 || col >= 9 || row < 0 || row >= 5)//必须点到土地上
            return;
        else
        {
            if(isFieldPlantable[row][col] == true && hasFieldPlanted[row][col] == 0)//如果可以种食物
            {
                if(isSettingPea == true && ableToSetPea == true && numOfSun >= 100)//种豌豆
                {

                    //几何位置设计
                    peaArray[row][col] = new Pea(ui->centralwidget);
                    peaArray[row][col]->setGeometry(120 + 82 * col, 80 + 100*row,82,100);

                    peaArray[row][col]->row = row;
                    peaArray[row][col]->col = col;//修改向日葵内部参数

                    isSettingPea = false;
                    ableToSetPea = false;//修改种植植物状态的参数

                    isFieldPlantable[row][col] = false;
                    hasFieldPlanted[row][col] = 2;//修改关于土地的参数

                    if(isSunFlowerCooling == false)
                    {
                        sunFlowerPushButton->setDisabled(false);//解放向日葵按钮
                    }
                    if(isWallNutCooling == false)
                    {
                        wallNutPushButton->setDisabled(false);//解放坚果按钮
                    }
                    shovelPushButton->setDisabled(false);//解放铲子按钮

                    this->setCursor(Qt::ArrowCursor);//把鼠标形状改回来

                    isPeaCooling = true;
                    peaPushButton->setDisabled(true);
                    peaCoolingDownTimer= new QTimer(0);
                    peaCoolingDownTimer->singleShot(peaArray[row][col]->coolingTime,this,SLOT(slot_setPeaPushButtonAbled()));
                    peaCoolingDownTimer->setInterval(50);
                    peaCoolingDownTimer->start();
                    peaCoolingDownTimer->singleShot(peaArray[row][col]->coolingTime,peaCoolingDownTimer,SLOT(stop()));
                    QObject::connect(peaCoolingDownTimer,SIGNAL(timeout()),this,SLOT(slot_peaCountDown()));
                    temp_leftPeaCoolingTime = peaArray[row][col]->coolingTime;//倒计时处理
                }

                if(isSettingSunFlower == true && ableToSetSunFlower == true && numOfSun >= 50)//种向日葵
                {

                    //几何位置的设计
                    sunFlowerArray[row][col] = new SunFlower(ui->centralwidget);
                    sunFlowerArray[row][col]->setGeometry(120 + 82 * col, 80 + 100*row,82,100);

                    sunFlowerArray[row][col]->row = row;
                    sunFlowerArray[row][col]->col = col;//修改向日葵内部参数

                    isSettingSunFlower = false;
                    ableToSetSunFlower = false;//修改种植植物状态的参数

                    isFieldPlantable[row][col] = false;
                    hasFieldPlanted[row][col] = 1;//修改关于土地的参数

                    if(isPeaCooling == false)
                    {
                        peaPushButton->setDisabled(false);//解放豌豆按钮
                    }
                    if(isWallNutCooling == false)
                    {
                        wallNutPushButton->setDisabled(false);//解放坚果按钮
                    }
                    shovelPushButton->setDisabled(false);//解放铲子按钮

                    this->setCursor(Qt::ArrowCursor);//把鼠标形状改回来

                    isSunFlowerCooling = true;
                    sunFlowerPushButton->setDisabled(true);
                    sunFlowerCoolingDownTimer = new QTimer(0);
                    sunFlowerCoolingDownTimer->singleShot(sunFlowerArray[row][col]->coolingTime,this,SLOT(slot_setSunFlowerPushButtonAbled()));
                    sunFlowerCoolingDownTimer->setInterval(50);
                    sunFlowerCoolingDownTimer->start();
                    sunFlowerCoolingDownTimer->singleShot(sunFlowerArray[row][col]->coolingTime,sunFlowerCoolingDownTimer,SLOT(stop()));
                    QObject::connect(sunFlowerCoolingDownTimer,SIGNAL(timeout()),this,SLOT(slot_sunFlowerCountDown()));
                    temp_leftSunFlowerCoolingTime = sunFlowerArray[row][col]->coolingTime;//倒计时处理

                }

                if(isSettingWallNut == true && ableToSetWallNut == true && numOfSun >= 50 )//种坚果
                {

                    wallNutArray[row][col] = new WallNut(ui->centralwidget);
                    wallNutArray[row][col]->setGeometry(120 + 82 * col, 80 + 100*row,82,100);

                    wallNutArray[row][col]->row = row;
                    wallNutArray[row][col]->col = col;//修改向日葵内部参数

                    isSettingWallNut = false;
                    ableToSetWallNut = false;//修改种植植物状态的参数

                    isFieldPlantable[row][col] = false;
                    hasFieldPlanted[row][col] = 3;//修改关于土地的参数

                    if(isPeaCooling == false)
                    {
                        peaPushButton->setDisabled(false);//解放豌豆按钮
                    }
                    if(isSunFlowerCooling == false)
                    {
                        sunFlowerPushButton->setDisabled(false);//解放向日葵按钮
                    }
                    shovelPushButton->setDisabled(false);//解放铲子按钮

                    this->setCursor(Qt::ArrowCursor);//把鼠标形状改回来

                    isWallNutCooling = true;
                    wallNutPushButton->setDisabled(true);
                    wallNutCoolingDownTimer = new QTimer(0);
                    wallNutCoolingDownTimer->singleShot(wallNutArray[row][col]->coolingTime,this,SLOT(slot_setWallNutPushButtonAbled()));
                    wallNutCoolingDownTimer->setInterval(50);
                    wallNutCoolingDownTimer->start();
                    wallNutCoolingDownTimer->singleShot(wallNutArray[row][col]->coolingTime,wallNutCoolingDownTimer,SLOT(stop()));
                    QObject::connect(wallNutCoolingDownTimer,SIGNAL(timeout()),this,SLOT(slot_wallNutCountDown()));
                    temp_leftWallNutCoolingTime = wallNutArray[row][col]->coolingTime;//倒计时处理

                }
            }

            else if(isFieldPlantable[row][col] == false && hasFieldPlanted[row][col] > 0)//该块土地上有植物
            {
                if(isToShovelPlants == true && ableToShovelPlants == true)//处于可铲除的状态
                {
                    //播放声音
                    mediaPlayer_shovel->play();

                    if(isPeaCooling == false)
                    {
                        peaPushButton->setDisabled(false);//解放豌豆按钮
                    }
                    if(isSunFlowerCooling == false)
                    {
                        sunFlowerPushButton->setDisabled(false);//解放向日葵按钮
                    }
                    if(isWallNutCooling == false)
                    {
                        wallNutPushButton->setDisabled(false);//解放坚果按钮
                    }

                    isFieldPlantable[row][col] = true;
                    hasFieldPlanted[row][col] = 0;//修改土地状态

                    if(peaArray[row][col] != nullptr)
                    {
                        delete peaArray[row][col];
                        peaArray[row][col] = nullptr;//删除一株豌豆并让其指向空指针
                    }
                    if(sunFlowerArray[row][col] != nullptr)
                    {
                        delete sunFlowerArray[row][col];
                        sunFlowerArray[row][col] = nullptr;//删除一株向日葵并让其指向空指针
                    }
                    if(wallNutArray[row][col] != nullptr)
                    {
                        delete wallNutArray[row][col];
                        wallNutArray[row][col] = nullptr;//删除一颗坚果并让其指向空指针
                    }
                }
            }
        }

    }
    else
        return;
}

//点击豌豆卡片触发的slot
void GameWindow::slot_clickPeaPushButton()
{
    //播放点击的音效
    mediaPlayer_buttonClicked->play();

    if(isSettingPea == false)
    {
        isSettingPea = true;
        ableToSetPea = true;//修改种植状态

        if(isSunFlowerCooling == false)
        {
            sunFlowerPushButton->setDisabled(true);//静默向日葵按钮
        }
        if(isWallNutCooling == false)
        {
            wallNutPushButton->setDisabled(true);//静默坚果按钮
        }
        shovelPushButton->setDisabled(true);//静默铲子按钮

        this->setCursor(QPixmap(":/new/Pea/Peashooter_0.png"));//改鼠标形状
    }
    else
    {
        isSettingPea = false;
        ableToSetPea = false;//修改种植状态

        if(isSunFlowerCooling == false)
        {
            sunFlowerPushButton->setDisabled(false);//解放向日葵按钮
        }
        if(isWallNutCooling == false)
        {
            wallNutPushButton->setDisabled(false);//解放坚果按钮
        }
        shovelPushButton->setDisabled(false);//解放铲子按钮

        this->setCursor(Qt::ArrowCursor);//改鼠标形状
    }
}

//点击向日葵卡片触发的slot
void GameWindow::slot_clickSunFlowerPushButton()
{
    //播放点击的音效
    mediaPlayer_buttonClicked->play();

    if(isSettingSunFlower == false)
    {
        isSettingSunFlower = true;
        ableToSetSunFlower = true;//修改种植状态

        if(isPeaCooling == false)
        {
            peaPushButton->setDisabled(true);//静默豌豆按钮
        }
        if(isWallNutCooling == false)
        {
            wallNutPushButton->setDisabled(true);//静默坚果按钮
        }
        shovelPushButton->setDisabled(true);//静默铲子按钮

        this->setCursor(QPixmap(":/new/SunFlower/SunFlower0.png"));//改鼠标形状

    }
    else
    {
        isSettingSunFlower = false;
        ableToSetSunFlower = false;//修改种植状态

        if(isPeaCooling == false)
        {
            peaPushButton->setDisabled(false);//解放豌豆按钮
        }
        if(isWallNutCooling == false)
        {
            wallNutPushButton->setDisabled(false);//解放坚果按钮
        }
        shovelPushButton->setDisabled(false);//解放铲子按钮

        this->setCursor(Qt::ArrowCursor);//改鼠标形状
    }
}

//点击坚果卡片触发的slot
void GameWindow::slot_clickWallNutPushButton()
{
    //播放点击的音效
    mediaPlayer_buttonClicked->play();

    if(isSettingWallNut == false)
    {
        isSettingWallNut = true;
        ableToSetWallNut = true;//修改种植状态

        if(isPeaCooling == false)
        {
            peaPushButton->setDisabled(true);//静默豌豆按钮
        }
        if(isSunFlowerCooling == false)
        {
            sunFlowerPushButton->setDisabled(true);//静默向日葵按钮
        }
        shovelPushButton->setDisabled(true);//静默铲子按钮

        this->setCursor(QPixmap(":/new/WallNut/WallNut0.png"));//改鼠标形状
    }
    else
    {
        isSettingWallNut = false;
        ableToSetWallNut = false;//修改种植状态

        if(isPeaCooling == false)
        {
            peaPushButton->setDisabled(false);//解放豌豆按钮
        }
        if(isSunFlowerCooling == false)
        {
            sunFlowerPushButton->setDisabled(false);//解放向日葵按钮
        }
        shovelPushButton->setDisabled(false);//解放铲子按钮

        this->setCursor(Qt::ArrowCursor);//改鼠标形状
    }

}

//点击铲子时触发的事件
void GameWindow::slot_clickShovelPushButton()
{
    //播放点击的音效
    mediaPlayer_buttonClicked->play();

    if(isToShovelPlants == false)
    {
        isToShovelPlants = true;
        ableToShovelPlants = true;//修改铲子状态

        if(isPeaCooling == false)
        {
            peaPushButton->setDisabled(true);//静默豌豆按钮
        }
        if(isSunFlowerCooling == false)
        {
            sunFlowerPushButton->setDisabled(true);//静默向日葵按钮
        }
        if(isWallNutCooling == false)
        {
            wallNutPushButton->setDisabled(true);//静默坚果按钮
        }

        this->setCursor(QPixmap(":/new/Shovel/Shovel.png"));//改鼠标形状
    }
    else
    {
        isToShovelPlants = false;
        ableToShovelPlants = false;//修改铲子状态

        if(isPeaCooling == false)
        {
            peaPushButton->setDisabled(false);//解放豌豆按钮
        }
        if(isSunFlowerCooling == false)
        {
            sunFlowerPushButton->setDisabled(false);//解放向日葵按钮
        }
        if(isWallNutCooling == false)
        {
            wallNutPushButton->setDisabled(false);//解放坚果按钮
        }

        this->setCursor(Qt::ArrowCursor);//改鼠标形状
    }
}

//场景滚动函数
void GameWindow::scrollBackgroundImage()
{
    QTimer *tempTimer = new QTimer(this);
    tempTimer->setInterval(40);
    tempTimer->start();
    QObject::connect(tempTimer,SIGNAL(timeout()),this,SLOT(slot_showBackgroundImage()));
}

//不断拷贝不同图片
void GameWindow::slot_showBackgroundImage()
{
    if(numOfBImgRightMove<50)
    {
    QImage *tempImage = new QImage(":/new/gamaWindow/background1.png");
    *backGroundImg =  tempImage->copy(10*numOfBImgRightMove,0,900,600) ;
    myBackGroundLabel->setPixmap(QPixmap::fromImage(*backGroundImg));
    numOfBImgRightMove++;
    }
    else if(numOfBImgLeftMove<38)
    {
        QImage *tempImage = new QImage(":/new/gamaWindow/background1.png");
        *backGroundImg =  tempImage->copy(500-10*numOfBImgLeftMove,0,900,600) ;
        myBackGroundLabel->setPixmap(QPixmap::fromImage(*backGroundImg));
        numOfBImgLeftMove++;
    }
    else
        return;
}

GameWindow::~GameWindow()
{
    delete ui;
}
