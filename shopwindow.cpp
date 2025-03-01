#include "shopwindow.h"
#include "global.h"
ShopWindow::ShopWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //初始化窗口大小
    setFixedSize(500,500);

    //设置窗口标题
    setWindowTitle("商店");
    deliveryCenterLevel = 1; // 初始交付中心等级
    miningSiteLevel = 1; // 初始开采物所在地块等级

    //准备音效
    moneyconsumed=new QSoundEffect;
    moneyconsumed->setSource(QUrl::fromLocalFile(":/res/music/consumed.wav"));
    moneyconsumed->setLoopCount(1);  //循环次数
    moneyconsumed->setVolume(0.3f); //音量  0~1之间

    // 创建标签
    coinLabel = new QLabel("金币数目: " + QString::number(gold), this);
    coinLabel->setGeometry(10, 10, 300, 30);

    deliveryCenterLabel = new QLabel("交付中心等级: " + QString::number(deliveryCenterLevel), this);
    deliveryCenterLabel->setGeometry(10, 50, 300, 30);

    miningSiteLabel = new QLabel("开采物所在地块等级: " + QString::number(miningSiteLevel), this);
    miningSiteLabel->setGeometry(10, 90, 300, 30);

    goldRewardLabel = new QLabel("开采物交付利润: " + QString::number(goldReward), this);
    goldRewardLabel->setGeometry(10, 130, 480, 30);

    // 创建按钮
    deliveryCenterButton = new QPushButton("升级交付中心 消耗600", this);

    deliveryCenterButton->setGeometry(50, 170, 400, 80);
    connect(deliveryCenterButton, &QPushButton::clicked, this, &ShopWindow::upgradeDeliveryCenter);

    miningSiteButton = new QPushButton("升级开采物所在地块 消耗100", this);
    miningSiteButton->setGeometry(50, 260, 400, 80);
    connect(miningSiteButton, &QPushButton::clicked, this, &ShopWindow::upgradeMiningSite);

    goldRewardButton = new QPushButton("升级金币奖励 消耗500", this);
    goldRewardButton->setGeometry(50, 350, 400, 80);
    connect(goldRewardButton, &QPushButton::clicked, this, &ShopWindow::upgradeGoldReward);

    setStyleSheet("background-color: #222222; color: white;");

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(12);

    coinLabel->setFont(font);
    deliveryCenterLabel->setFont(font);
    miningSiteLabel->setFont(font);
    goldRewardLabel->setFont(font);

    deliveryCenterButton->setFont(font);
    miningSiteButton->setFont(font);
    goldRewardButton->setFont(font);

    deliveryCenterButton->setStyleSheet("QPushButton { background-color: #555555; color: white; border-radius: 5px; }"
                                        "QPushButton:hover { background-color: #888888; }");

    miningSiteButton->setStyleSheet("QPushButton { background-color: #555555; color: white; border-radius: 5px; }"
                                    "QPushButton:hover { background-color: #888888; }");

    goldRewardButton->setStyleSheet("QPushButton { background-color: #555555; color: white; border-radius: 5px; }"
                                    "QPushButton:hover { background-color: #888888; }");
}

void ShopWindow::upgradeDeliveryCenter()
{
    // 执行升级和一系列操作
    if(gold>=600&&deliveryCenterLevel==1){
        deliveryCenterLevel++;
        moneyconsumed->play();
        //修改map
        Map[10][17]=-5;
        Map[10][18]=-5;
        Map[10][19]=-5;
        Map[10][20]=-5;
        Map[11][17]=-5;
        Map[11][20]=-5;
        Map[12][17]=-5;
        Map[12][20]=-5;
        Map[13][17]=-5;
        Map[13][18]=-5;
        Map[13][19]=-5;
        Map[13][20]=-5;
        gold-=600;
    }


    // 更新标签文本
    coinLabel->setText("金币数目: "+QString::number(gold));
    deliveryCenterLabel->setText("交付中心等级: " + QString::number(deliveryCenterLevel));
}

void ShopWindow::upgradeMiningSite()
{
    // 执行升级和一系列操作
    if(gold>=100){
        moneyconsumed->play();
        miningSiteLevel++;
        //修改map
        // 随机选择行和列的索引
        int cnt=1;
        int row = std::rand() % GAME_HEIGHT;
        int col = std::rand() % GAME_WIDTH;
        while(cnt>0){
            // 根据选中的格子进行赋值
            if (Map[row/GRID_SIZE][col/GRID_SIZE] == 0 &&
                (row+col)%2==1)
            {
                Map[row/GRID_SIZE][col/GRID_SIZE] = -1;
                emit addNewResource(row/GRID_SIZE, col/GRID_SIZE);
                cnt--;
            }
            else if(Map[row/GRID_SIZE][col/GRID_SIZE] == 0 &&
                       (row+col)%2==0)
            {
                Map[row/GRID_SIZE][col/GRID_SIZE] = -2;
                emit addNewResource(row/GRID_SIZE, col/GRID_SIZE);

                cnt--;
            }
            else{
                row = std::rand() % GAME_HEIGHT;
                col = std::rand() % GAME_WIDTH;
            }
        }
        gold-=100;

    }


    // 更新标签文本
    coinLabel->setText("金币数目: "+QString::number(gold));
    miningSiteLabel->setText("开采物所在地块等级: " + QString::number(miningSiteLevel));
}

void ShopWindow::upgradeGoldReward()
{
    // 执行升级和一系列操作
    if(gold>=500){
        moneyconsumed->play();
        goldReward+=5;
        gold-=500;
    }

    // 更新标签文本
    coinLabel->setText("金币数目: "+QString::number(gold));
    goldRewardLabel->setText("开采物交付利润: " + QString::number(goldReward));
}
void ShopWindow::closeEvent(QCloseEvent* e){
    emit closewindow();
    this->close();
}
