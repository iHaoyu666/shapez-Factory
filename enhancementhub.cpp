#include "enhancementhub.h"
#include <QHBoxLayout>
#include <QLabel>
EnhancementHub::EnhancementHub(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1000,250);

    // 创建标签
    QLabel *titleLabel = new QLabel("请选择一个效率进行强化", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setGeometry(0, 20, width(), 30);  // 设置标签的位置和大小

    // 创建按钮
    miningButton = new QPushButton("加快开采速率", this);
    conveyorButton = new QPushButton("加快传送速率", this);
    cuttingButton = new QPushButton("加快切割速率", this);

    int buttonWidth = 200;
    int buttonHeight = 75;
    int buttonSpacing = 20;
    int buttonX = (width() - (buttonWidth * 3 + buttonSpacing * 2)) / 2;
    int buttonY = titleLabel->y() + titleLabel->height() + buttonSpacing;
    miningButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    buttonX += buttonWidth + buttonSpacing;
    conveyorButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    buttonX += buttonWidth + buttonSpacing;
    cuttingButton->setGeometry(buttonX, buttonY, buttonWidth, buttonHeight);

    // 添加图片
    QLabel* miningImageLabel = new QLabel(this);
    QPixmap miningPixmap(":/res/pic/buildings/2.png");
    miningPixmap = miningPixmap.scaled(buttonWidth/2, buttonHeight/2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    miningImageLabel->setPixmap(miningPixmap);
    miningImageLabel->setAlignment(Qt::AlignCenter);
    miningImageLabel->setGeometry(miningButton->x(), miningButton->y() + miningButton->height() + buttonSpacing, buttonWidth, buttonHeight);

    QLabel* conveyorImageLabel = new QLabel(this);
    QPixmap conveyorPixmap(":/res/pic/buildings/0.png");
    conveyorPixmap = conveyorPixmap.scaled(buttonWidth/2, buttonHeight/2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    conveyorImageLabel->setPixmap(conveyorPixmap);
    conveyorImageLabel->setAlignment(Qt::AlignCenter);
    conveyorImageLabel->setGeometry(conveyorButton->x(), conveyorButton->y() + conveyorButton->height() + buttonSpacing, buttonWidth, buttonHeight);

    QLabel* cuttingImageLabel = new QLabel(this);
    QPixmap cuttingPixmap(":/res/pic/buildings/1.png");
    cuttingPixmap = cuttingPixmap.scaled(buttonWidth/2, buttonHeight/2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    cuttingImageLabel->setPixmap(cuttingPixmap);
    cuttingImageLabel->setAlignment(Qt::AlignCenter);
    cuttingImageLabel->setGeometry(cuttingButton->x(), cuttingButton->y() + cuttingButton->height() + buttonSpacing, buttonWidth, buttonHeight);


    // 连接按钮的clicked信号到相应的槽函数，并发送相应的信号给GameWindow窗口
    connect(miningButton, &QPushButton::clicked, this, [&]() {
        emit miningRateIncreased();
        hide();

    });
    connect(conveyorButton, &QPushButton::clicked, this, [&]() {
        emit conveyorRateIncreased();
        hide();

    });
    connect(cuttingButton, &QPushButton::clicked, this, [&]() {
        emit cuttingRateIncreased();
        hide();

    });
}
void EnhancementHub::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    miningButton->show();
    conveyorButton->show();
    cuttingButton->show();
}
void EnhancementHub::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);

    miningButton->hide();
    conveyorButton->hide();
    cuttingButton->hide();
}
