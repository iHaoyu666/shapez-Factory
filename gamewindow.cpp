#include "gamewindow.h"
#include "config.h"
#include "cuttertool.h"
#include "extractortool.h"
#include "trashtool.h"
#include "translatortool.h"

gamewindow::gamewindow(QWidget *parent)
    : QWidget(parent)
{
    QPainter painter(this);
    initScene();
}
void gamewindow::initScene(){
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

}
void gamewindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    drawMap(painter);
    drawToolSelection(painter);
    painter.end();
}
void gamewindow::drawMap(QPainter& painter){
    // 格子大小
    int gridSize = GRID_SIZE;

    // 绘制横线
    for (int y = 0; y <= height() / gridSize; ++y) {
        int yPos = y * gridSize;
        painter.drawLine(0, yPos, width(), yPos);
    }

    // 绘制竖线
    for (int x = 0; x <= width() / gridSize; ++x) {
        int xPos = x * gridSize;
        painter.drawLine(xPos, 0, xPos, height());
    }

    //加载交付中心图片
    QPixmap deliveryCenterPixmap(":/res/pic/buildings/3-0.png");

    // 计算交付中心的位置
    int centerX = width() / 2 - gridSize ;
    int centerY = height() / 2 - gridSize ;

    // 绘制交付中心图片
    QRect deliveryCenterRect(centerX, centerY, gridSize * 2, gridSize * 2);
    painter.drawPixmap(deliveryCenterRect, deliveryCenterPixmap);
}

void gamewindow::drawToolSelection(QPainter& painter){
    // 工具栏大小
    const int toolbarWidth = GAME_WIDTH * 0.5;
    const int toolbarHeight = 100;

    // 工具栏的位置
    int toolbarX = (width() - toolbarWidth) / 2;
    int toolbarY = height() - toolbarHeight - 20; // 距离底部一定的间距

    // 加载工具图片
    QPixmap ConveyorPixmap(":/res/pic/buildings/0.png");
    QPixmap CutterPixmap(":/res/pic/buildings/1.png");
    QPixmap ExcavatorPixmap(":/res/pic/buildings/2.png");
    QPixmap TrashPixmap(":/res/pic/buildings/4.png");

    QColor toolbarColor(128, 128, 128, 128);
    // 绘制工具栏背景
    painter.setBrush(toolbarColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(toolbarX, toolbarY, toolbarWidth, toolbarHeight);

    // 绘制工具图片
    int toolSize = 75; // 工具图片的大小
    int toolSpacing = 50; // 工具图片之间的间距

    QPoint tool0Pos(toolbarX + (toolbarWidth - toolSize * 4 - toolSpacing * 3) / 2, toolbarY + (toolbarHeight - toolSize) / 2);
    QPoint tool1Pos = tool0Pos + QPoint(toolSize + toolSpacing, 0);
    QPoint tool2Pos = tool1Pos + QPoint(toolSize * 2 + toolSpacing, 0);
    QPoint tool3Pos = tool2Pos + QPoint(toolSize + toolSpacing, 0);

    painter.drawPixmap(tool0Pos, ConveyorPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool1Pos, CutterPixmap.scaled(toolSize * 2, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool2Pos, ExcavatorPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool3Pos, TrashPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
}

void gamewindow::wheelEvent(QWheelEvent* event){

}
