//#include "resource.h"

//resource::resource(int x, int y, int direction,QObject *parent = nullptr)
//    :currentX(x), currentY(y), direction(0), QObject(parent)
//{
//}

//void resource::moveWithConveyor(double rate, int direction)
//{
//    // 更新资源的速率和方向
//    this->rate = rate;
//    this->direction = direction;

//    // 检查传送带方向上的下一个位置是否是传送带
//    int nextX = currentX;
//    int nextY = currentY;
//    switch (direction)
//    {
//    case 0: // 向上
//        nextY--;
//        break;
//    case 90: // 向右
//        nextX++;
//        break;
//        // 添加其他方向的处理逻辑
//    }

//    // 检查下一个位置是否是传送带
//    if (Map[nextY][nextX] == 1)
//    {
//        // 生成新的资源
//        resource* newResource = new resource(this); // 创建新资源对象
//        newResource->moveWithConveyor(rate, direction); // 设置新资源的速率和方向
//        emit resourceGenerated(newResource); // 发送资源生成信号

//        // 更新地图，将新资源放置在下一个位置
//        Map[nextY][nextX] = -1; // 假设新资源是可开采矿物1，您可以根据具体需求进行调整
//    }

//    // 移动当前资源到下一个位置
//    // 更新地图，将当前资源从当前位置移除
//    Map[currentY][currentX] = 0;

//    // 更新当前位置
//    currentX = nextX;
//    currentY = nextY;

//    // 更新地图，将当前资源放置在新位置
//    Map[currentY][currentX] = -1; // 假设当前资源是可开采矿物1，您可以根据具体需求进行调整
//}
