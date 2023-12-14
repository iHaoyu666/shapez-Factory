#include "resource.h"
#include <QDebug>
void resource::draw(QPainter &painter){
    QPixmap resource1Image(":/res/pic/pieces/resource1.png");
    QPixmap resource2Image(":/res/pic/pieces/resource2.png");
    QPixmap resource2clipImage(":/res/pic/pieces/2-2.png");
    switch(kind){
    case 1:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource1Image);
        break;
    case 2:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource2Image);
        break;
    case 3:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource2clipImage);
        break;

    }
}

void resource::moveWithConveyor()//int direction
{
//    // 更新资源的速率和方向
//    this->direction = direction;

    // 检查传送带方向上的下一个位置是否是传送带
    int nextX = currentX;
    int nextY = currentY;
    switch (direction)
    {
    case 0: // 向上
        nextY-=rate;
        break;
    case 90: // 向右
        nextX+=rate;
        break;
    case 180:
        nextY+=rate;
        break;
    case 270:
        nextX-=rate;
        break;
    default:
        break;
    }

    // 检查下一个位置是否是传送带 或者是资源所在地段
    if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 1||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == -3||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == -4)
    {
        qDebug()<<"开始移动"<<currentX<<currentY<<nextX<<nextY;
        //更新位置
        currentX=nextX;
        currentY=nextY;

    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 3)//下一个位置垃圾桶
    {
        this->deleteLater();
    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 4)//下一个位置剪切器剪切头
    {
        if(kind==2){
            kind=3;
            switch (direction)
            {
            case 0: // 向上
                currentY-=GRID_SIZE;
                break;
            case 90: // 向右
                currentX+=GRID_SIZE;
                break;
            case 180:
                currentY+=GRID_SIZE;
                break;
            case 270:
                currentX-=GRID_SIZE;
                break;
            default:
                break;
            }
        }
//        resource* newResource = new resource(this); // 创建新资源对象
//        newResource->moveWithConveyor(direction); // 设置新资源的速率和方向
//        emit resourceGenerated(newResource); // 发送资源生成信号

        // 更新地图，将新资源放置在下一个位置

    }
    else if (Map[nextY][nextX] == 4)//下一个位置剪切器没用的口
    {

    }
    else if(Map[nextY/GRID_SIZE][nextX/GRID_SIZE] ==-5 )//交付中心
    {
        donePieces++;
        this->deleteLater();
    }
    else // 只是没找到工具 则顺时针寻找有没有传送带
    {
        int clockwiseDirections[] = {90, 270}; // 顺时针方向数组

        for (int i = 0; i < 2; i++) {
            int newDirection = (direction + clockwiseDirections[i]) % 360;
            int newX = currentX;
            int newY = currentY;
            int nextGRIDX=currentX/GRID_SIZE;
            int nextGRIDY=currentY/GRID_SIZE;
            switch (newDirection) {
            case 0: // 向上
                newY -= rate;
                nextGRIDY--;
                break;
            case 90: // 向右
                newX += rate;
                nextGRIDX++;
                break;
            case 180: // 向下
                newY += rate;
                nextGRIDY++;
                break;
            case 270: // 向左
                newX -= rate;
                nextGRIDX--;
                break;
            default:
                break;
            }

            // 检查新方向上的下一个位置是否是传送带
            if (Map[nextGRIDY][nextGRIDX] == 1) {
                // 更新位置和方向
                currentX = newX;
                currentY = newY;
                this->direction = newDirection;
                break;
            }
        }
    }


}
