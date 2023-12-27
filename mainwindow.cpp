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
    gamewindow *gwindow=new gamewindow;
    gwindow->show();
    this->hide();
}

void MainWindow::loadGame() {
    QMessageBox::information(this, "继续游戏", "存档读取中……");
    //读取存档操作 TODO
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

    QPushButton *shopButton = new QPushButton("商店", this);
    shopButton->setGeometry(START_WIDTH * 0.5 - 75, START_HEIGHT * 0.5 + 210, 150, 100);
    connect(shopButton, &QPushButton::clicked, this, &MainWindow::openShop);
}
