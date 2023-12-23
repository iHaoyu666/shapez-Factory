#include "enhancementhub.h"
#include <QHBoxLayout>
EnhancementHub::EnhancementHub(QWidget *parent)
    : QWidget{parent}
{
    // 创建按钮
    miningButton = new QPushButton("加快开采速率", this);
    conveyorButton = new QPushButton("加快传送速率", this);
    cuttingButton = new QPushButton("加快切割速率", this);

    // 将按钮添加到布局中
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(miningButton);
    layout->addWidget(conveyorButton);
    layout->addWidget(cuttingButton);

    // 连接按钮的clicked信号到相应的槽函数，并发送相应的信号给GameWindow窗口
    connect(miningButton, &QPushButton::clicked, this, [this]() {
        emit miningRateIncreased();
        close();
    });
    connect(conveyorButton, &QPushButton::clicked, this, [this]() {
        emit conveyorRateIncreased();
        close();
    });
    connect(cuttingButton, &QPushButton::clicked, this, [this]() {
        emit cuttingRateIncreased();
        close();
    });
}

