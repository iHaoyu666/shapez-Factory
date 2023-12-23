#include "resource.h"
#include <QDebug>
void resource::draw(QPainter &painter){
    if (state==0){
        return;
    }
    QPixmap resource1Image(":/res/pic/pieces/circle1.png");
    QPixmap resource2Image(":/res/pic/pieces/resource2.png");
    QPixmap resource1clipImage(":/res/pic/pieces/circle1uphalf.png");
    switch(kind){
    case 1:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource1Image);
        break;
    case 2:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource2Image);
        break;
    case 3:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource1clipImage);
        break;

    }
}

void resource::moveWithConveyor(int _rate)//int direction
{
//    // 更新资源的速率和方向
//    this->direction = direction;
    rate = _rate;
    // 检查传送带方向上的下一个位置是否是传送带
    int nextX = currentX;
    int nextY = currentY;
    int nextGridX=currentX/GRID_SIZE; //存储沿运动方向走到的下一个格子的位置
    int nextGirdY=currentY/GRID_SIZE;
    switch (direction)
    {
    case 0: // 向上
        nextY-=rate;
        nextGirdY--;
        break;
    case 90: // 向右
        nextX+=rate;
        nextGridX++;
        break;
    case 180:  //向下
        nextY+=rate;
        nextGirdY++;
        break;
    case 270:  //向左
        nextX-=rate;
        nextGridX--;
        break;
    default:
        break;
    }
    if(Map[nextGirdY][nextGridX]!=1&&(nextX%GRID_SIZE==0.5*GRID_SIZE&&nextY%GRID_SIZE==0.5*GRID_SIZE)){
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
    // 检查下一个位置是否是传送带 或者是资源所在地段
    if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 1||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == -3||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == -4)
    {
        //更新位置
        currentX=nextX;
        currentY=nextY;

    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 3)//下一个位置垃圾桶
    {
        state=0;
        return;
    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 4)//下一个位置剪切器剪切头
    {
        if(kind==1){
            switch (direction)
            {
            case 0: // 向上
                if (Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE+1] == 3)
                {
                    currentY-=GRID_SIZE;
                    kind=3;
                }
                break;
            case 90: // 向右
                if (Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE+1] == 3)
                {
                    currentX+=GRID_SIZE;
                    kind=3;
                }
                break;
            case 180:
                if (Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE-1] == 3)
                {
                    kind=3;
                    currentY+=GRID_SIZE;
                }
                break;
            case 270:
                if (Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE-1] == 3)
                {
                    kind=3;
                    currentX-=GRID_SIZE;
                }
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
        state=0;
        return;
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
