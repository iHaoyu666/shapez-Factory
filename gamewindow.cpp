#include "gamewindow.h"
#include "config.h"
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
    painter.end();
}
void gamewindow::drawMap(QPainter& painter){
    QPixmap gridPixmap(":/res/grid.png"); // 加载格子图片

    QSize pixmapSize = gridPixmap.size();
    int pixmapWidth = pixmapSize.width();
    int pixmapHeight = pixmapSize.height();

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            // 计算格子的位置
            int posX = x * pixmapWidth;
            int posY = y * pixmapHeight;
            QPoint gridPos(posX, posY);

            // 在地图上绘制格子图片
            painter.drawPixmap(gridPos, gridPixmap);
        }
    }
}

void gamewindow::drawToolSelection(QPainter&){

}

void gamewindow::wheelEvent(QWheelEvent* event){

}
