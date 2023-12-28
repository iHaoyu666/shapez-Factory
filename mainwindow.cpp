#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"
#include "gamewindow.h"
#include "shopwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initScene();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame() {
    QMessageBox::information(this, "开始游戏", "游戏初始化中……");
    newgameclean();     //重置全局属性

    gamewindow *gwindow=new gamewindow;
    gwindow->show();
    this->hide();
    connect(gwindow,&gamewindow::windowclose,this, &MainWindow::show);
    connect(gwindow,&gamewindow::windowclose,this, &MainWindow::saveData);//游戏一返回主菜单就存档
}

void MainWindow::loadGame() {
    QMessageBox::information(this, "继续游戏", "存档读取中……");
    QString filePath = "./player1.txt";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        // 读取地图数据
        for (int i = 0; i < mapHeight; ++i)
        {
            for (int j = 0; j < mapWidth; ++j)
            {
                stream >> Map[i][j];
            }
        }

        // 读取其他数据
        stream >> gold;
        stream >> goldReward;
        stream >> deliveryCenterLevel;
        stream >> miningSiteLevel;

        file.close();
        qDebug() << "Data loaded.";
    }
    else
    {
        qDebug() << "Unable to open the file for reading.";
    }
    gamewindow *gwindow=new gamewindow;
    gwindow->show();
    this->hide();
    connect(gwindow,&gamewindow::windowclose,this, &MainWindow::show);
    connect(gwindow,&gamewindow::windowclose,this, &MainWindow::saveData);//游戏一返回主菜单就存档
}

void MainWindow::showGameInfo() {
    QMessageBox::information(this, "游戏说明", "This is a game. Have fun!");//此处在设计完之后添加游戏说明
}

void MainWindow::openShop()
{
    QMessageBox::information(this, "商店", "打开商店窗口");

    // 创建商店窗口
    ShopWindow *shopWindow = new ShopWindow(this);
    shopWindow->show();
    connect(shopWindow, &ShopWindow::addNewResource, this, [=](int x, int y) {
        points.push_back(QPoint(x, y));

    });
}

void MainWindow::initScene()
{
    //初始化窗口大小
    setFixedSize(START_WIDTH,START_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置背景图片
    QPixmap pixmap(":/res/background1.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    setAutoFillBackground(true);
    setPalette(palette);
    // 创建开始游戏按钮
    QPushButton *startButton = new QPushButton("开始游戏", this);
    startButton->setGeometry(START_WIDTH * 0.5-75, START_HEIGHT*0.5, 150, 100);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    // 创建读取存档按钮
    QPushButton *loadButton = new QPushButton("继续游戏", this);
    loadButton->setGeometry(START_WIDTH * 0.5-75, START_HEIGHT*0.5+70, 150, 100);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadGame);

    // 创建游戏说明按钮
    QPushButton *infoButton = new QPushButton("游戏说明", this);
    infoButton->setGeometry(START_WIDTH*0.5-75, START_HEIGHT*0.5+140, 150, 100);
    connect(infoButton, &QPushButton::clicked, this, &MainWindow::showGameInfo);

    // 创建商店按钮
    QPushButton *shopButton = new QPushButton("商店", this);
    shopButton->setGeometry(START_WIDTH * 0.5 - 75, START_HEIGHT * 0.5 + 210, 150, 100);
    connect(shopButton, &QPushButton::clicked, this, &MainWindow::openShop);
}
//void MainWindow::loadData() {   //读档
//    QString filePath="player1.txt";
//    QFile file(filePath);
//    if (file.open(QIODevice::ReadOnly)) {
//        QDataStream stream(&file);
//        for (int i = 0; i < mapHeight; ++i) {
//            for (int j = 0; j < mapWidth; ++j) {
//                stream >> Map[i][j];
//            }
//        }
//        stream >> gold;
//        stream >> goldReward;
//        stream >> deliveryCenterLevel;
//        stream >> miningSiteLevel;
//        file.close();
//    }
//}


void MainWindow::saveData() {               //存档

    QString filePath = "./player1.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);

        // 写入地图数据
        for (int i = 0; i < mapHeight; ++i)
        {
            for (int j = 0; j < mapWidth; ++j)
            {
                stream << Map[i][j] << " ";
            }
            stream << Qt::endl;
        }

        // 写入其他数据
        stream << gold << Qt::endl;
        stream << goldReward << Qt::endl;
        stream << deliveryCenterLevel << Qt::endl;
        stream << miningSiteLevel << Qt::endl;
        file.close();
        qDebug() << "Data saved.";
    }
    else
    {
        qDebug() << "Unable to open the file for writing.";
    }
    QString runPath = QCoreApplication::applicationDirPath() + "/player1.txt";
    runPath.replace(QString("/"),QString("\\"));
    qDebug() << runPath;
}

void MainWindow::newgameclean(){    //重置全局属性
    gold=0;
    goldReward=10;
    deliveryCenterLevel=1;
    miningSiteLevel=1;
    Map[10][17]=0;
    Map[10][18]=0;
    Map[10][19]=0;
    Map[10][20]=0;
    Map[11][17]=0;
    Map[11][20]=0;
    Map[12][17]=0;
    Map[12][20]=0;
    Map[13][17]=0;
    Map[13][18]=0;
    Map[13][19]=0;
    Map[13][20]=0;
    for(QPoint point:points){
        Map[point.x()][point.y()]=0;
    }
}









