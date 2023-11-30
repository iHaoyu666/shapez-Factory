#include "gamewindow.h"
#include "config.h"
gamewindow::gamewindow(QWidget *parent)
    : QWidget(parent)
{
    QPainter painter(this);
    initScene();
    setMouseTracking(true); // 开启鼠标跟踪
    scaleRatio = 1.0; // 初始化缩放比例
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
    QPixmap gridPixmap(":/res/grid.png"); // 加载格子图片

    // 原始格子大小
    const int originalGridSize = 40;

    // 缩小后的格子大小
    int scaledGridSize = originalGridSize / scaleRatio;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            // 计算原始格子的位置
            int originalPosX = x * originalGridSize;
            int originalPosY = y * originalGridSize;
            QPoint originalGridPos(originalPosX, originalPosY);

            // 缩小后格子的位置和大小
            int scaledPosX = originalPosX / scaleRatio;
            int scaledPosY = originalPosY / scaleRatio;
            QPoint scaledGridPos(scaledPosX, scaledPosY);

            // 在地图上绘制缩小后的格子图片
            painter.drawPixmap(scaledGridPos, gridPixmap);
        }
    }
}

void gamewindow::drawToolSelection(QPainter&){

}
void gamewindow::wheelEvent(QWheelEvent* event) {
    // 根据滚轮的滚动距离来调整缩放比例
    int delta = event->angleDelta().y();
    if (delta > 0) {
        scaleRatio *= 1.2;
    } else {
        scaleRatio /= 1.2;
    }

    // 限制缩放比例的范围
    if (scaleRatio < 1.0) {
        scaleRatio = 1.0;
    } else if (scaleRatio > 5.0) {
        scaleRatio = 5.0;
    }

    // 重绘窗口
    update();
}
