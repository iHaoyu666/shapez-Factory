#include "gamewindow.h"
#include "config.h"
#include "tool.h"
#include "cuttertool.h"
#include "extractortool.h"
#include "trashtool.h"
#include "translatortool.h"
#include "map.h"
#include <QTimer>
#include <QDebug>
#define MouClickRegion(X, Y, Width, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))

const int toolbarWidth = GAME_WIDTH * 0.5;
const int toolbarHeight = 100;

// 工具栏的位置
int toolbarX = (GAME_WIDTH - toolbarWidth) / 2;
int toolbarY = GAME_HEIGHT - toolbarHeight - 20; // 距离底部一定的间距


gamewindow::gamewindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setMouseTracking(true);
//    connect(this, &gamewindow::resourceBeingExcavated, this,[&](int kind, int x, int y, int angle) {
//        miningElements.push_back(std::make_tuple(QPoint(x, y), kind, angle));
//    });
    QPainter painter(this);

    refreshTimer = new QTimer(this);
    generateTimer= new QTimer(this);
    connect(generateTimer, &QTimer::timeout, this, [&]{
        for (const auto& element : qAsConst(miningElements)) {
            // 获取位置、种类和方向信息
            QPoint position = std::get<0>(element);
            int kind = std::get<1>(element);
            int angle = std::get<2>(element);


            // 在指定位置生成新的Resource类
            resource* newResource = new resource(kind, position.x(), position.y(), angle);
            qDebug()<<"新资源生成";
            // 将新资源添加到资源列表
            resources.push_back(newResource);
        }
    });

    connect(refreshTimer, &QTimer::timeout, this, QOverload<>::of(&gamewindow::update));
    generateTimer->start(5000);//生成资源速度
    refreshTimer->start(50);  // 设置刷新间隔，单位为毫秒

    //金钱标签
    moneyLable->move(20, 40);
    moneyLable->setFont(QFont("黑体", 20));
    moneyLable->setText(QString("金钱：%1").arg(money));
    //交付数量标签
    centerLable->move(GAME_WIDTH/2-GRID_SIZE, GAME_HEIGHT/2-GRID_SIZE);
    centerLable->setFont(QFont("黑体", 8));
    centerLable->setText(QString("已交付数量：%1").arg(money));
}

void gamewindow::paintEvent(QPaintEvent* event) {

    QPainter painter(this);
    drawMap(painter);
    drawToolSelection(painter);
    drawresource(painter);
    if (GetKeyState('R')<0&&isMousePressed) {
        QDateTime currentTime = QDateTime::currentDateTime();
        if (lastRotationTime.isNull() || lastRotationTime.msecsTo(currentTime) >= rotationInterval) {
            selectedTool->rotate(90);
            lastRotationTime = currentTime;
        }
    }

//    if (GetKeyState('ctrl') < 0 && isMousePressed&& selectedTool->getType()==ToolType::Conveyor){
//        std::vector<std::pair<int, int>> path; // 保存经过的格子坐标
//        QPoint mousePos = mapFromGlobal(QCursor::pos());
//        int startX = mousePos.x()/GRID_SIZE;
//        int startY = mousePos.y()/GRID_SIZE;

//        int prevX = startX;
//        int prevY = startY;
//        path.push_back(std::make_pair(startX, startY)); // 将起始格子坐标添加到路径中

//        while (isMousePressed) {
//            int mouseX = mousePos.x()/GRID_SIZE; // 获取鼠标当前所在的格子坐标
//            int mouseY = mousePos.y()/GRID_SIZE;

//            // 判断是否换了格子
//            if (mouseX != prevX || mouseY != prevY) {
//                // 添加当前格子坐标到路径中
//                path.push_back(std::make_pair(mouseX, mouseY));
//            }



//            // 更新前一个格子坐标
//            prevX = mouseX;
//            prevY = mouseY;
//        }

//        // 将记录的格子放置在传送带上
//        placeConveyorOnPath(path);
//    }
    for (const auto& tool : tools){
        tool->draw(painter);
    }
    for (auto resource: resources){
        resource->moveWithConveyor();
        resource->draw(painter);
    }
    if (selectedTool) {
        selectedTool->draw(painter);
    }
    painter.end();
}
void gamewindow::generateResource(int kind, int x, int y, int angle) {
    // 在资源区域生成新的Resource实例
    connect(refreshTimer, &QTimer::timeout, this, [this, kind, x, y, angle]() {
        // 在指定位置生成新的Resource类
        resource* newResource = new resource(kind, x, y, angle);
        // 将新资源添加到资源列表
        resources.push_back(newResource);
    });

    // 将新资源添加到资源列表
    }

//void addCornerConveyor(const std::vector<std::pair<int, int>>& path, int cornerX, int cornerY) {
//    // 根据拐点的坐标和路径中的前一个格子坐标判断拐弯的方向
//    int prevX = path.back().first;
//    int prevY = path.back().second;
//    int direction = getConveyorDirection(prevX, prevY, cornerX, cornerY);

//    // 在拐点处放置拐弯传送带
//    Map[cornerY][cornerX] = getConveyorType(direction);
//}

//void placeConveyorOnPath(const std::vector<std::pair<int, int>>& path) {
//    // 在路径上的每个格子上放置传送带
//    for (const auto& point : path) {
//        int x = point.first;
//        int y = point.second;
//        Map[y][x] = getConveyorType(Direction::Straight); // 假设放置直行传送带，您可以根据需求进行调整
//    }
//}

//int getConveyorDirection(int startX, int startY, int endX, int endY) {
//    // 根据起点和终点坐标计算传送带的方向
//    if (startX == endX) {
//        if (startY < endY) {
//            return Direction::Down; // 向下
//        } else {
//            return Direction::Up; // 向上
//        }
//    } else if (startY == endY) {
//        if (startX < endX) {
//            return Direction::Right; // 向右
//        } else {
//            return Direction::Left; // 向左
//        }
//    } else {
//        // 处理其他情况，如拐角传送带
//        // 根据需要进行实现
//    }
//}

//int getConveyorType(int direction) {
//    // 根据传送带的方向返回对应的传送带类型
//    switch (direction) {
//    case Direction::Up:
//        return ConveyorType::Up;
//    case Direction::Down:
//        return ConveyorType::Down;
//    case Direction::Left:
//        return ConveyorType::Left;
//    case Direction::Right:
//        return ConveyorType::Right;
//    // 处理其他传送带类型
//    default:
//        return ConveyorType::Straight;
//    }
//}
void gamewindow::drawMap(QPainter& painter){
    // 格子大小
    int gridSize = GRID_SIZE;

    QPen pen(Qt::lightGray);
    painter.setPen(pen);
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
    QPixmap deliveryCenterPixmap(":/res/pic/buildings/3.png");

    // 计算交付中心的位置
    int centerX = width() / 2 - 2* gridSize -10;
    int centerY = height() / 2 - 2* gridSize -10;

    // 绘制交付中心图片
    QRect deliveryCenterRect(centerX, centerY, gridSize * 4+20, gridSize * 4+20);
    painter.drawPixmap(deliveryCenterRect, deliveryCenterPixmap);


}

void gamewindow::drawToolSelection(QPainter& painter){

    // 加载工具图片
    QPixmap ConveyorPixmap(":/res/pic/buildings/0.png");
    QPixmap CutterPixmap(":/res/pic/buildings/1.png");
    QPixmap ExcavatorPixmap(":/res/pic/buildings/2.png");
    QPixmap GarbageCanPixmap(":/res/pic/buildings/4.png");

    QColor toolbarColor(128, 128, 128, 128);
    // 绘制工具栏背景
    painter.setBrush(toolbarColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(toolbarX, toolbarY, toolbarWidth, toolbarHeight);

    // 绘制工具图片
    int toolSize = GRID_SIZE; // 工具图片的大小
    int toolSpacing = 50; // 工具图片之间的间距
    //  0 传送带       1 剪切器       2 开采器       3 垃圾桶
    QPoint tool0Pos(toolbarX + (toolbarWidth - toolSize * 4 - toolSpacing * 3) / 2, toolbarY + (toolbarHeight - toolSize) / 2);
    QPoint tool1Pos = tool0Pos + QPoint(toolSize + toolSpacing, 0);
    QPoint tool2Pos = tool1Pos + QPoint(toolSize * 2 + toolSpacing, 0);
    QPoint tool3Pos = tool2Pos + QPoint(toolSize + toolSpacing, 0);

    painter.drawPixmap(tool0Pos, ConveyorPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool1Pos, CutterPixmap.scaled(toolSize * 2, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool2Pos, ExcavatorPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool3Pos, GarbageCanPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
}

void gamewindow::drawresource(QPainter& painter){
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int resourceCode = Map[y][x];
            if (resourceCode == -1||resourceCode == -3) {
                // 绘制可开采矿物1的图片资源
                QPixmap resourcePixmap(":/res/pic/pieces/resource1.png");  // 根据实际的图片路径和名称进行修改
                QRect rect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                painter.drawPixmap(rect, resourcePixmap);
            } else if (resourceCode == -2||resourceCode == -4) {
                // 绘制可开采矿物2的图片资源
                QPixmap resourcePixmap(":/res/pic/pieces/resource2.png");  // 根据实际的图片路径和名称进行修改
                QRect rect(x * GRID_SIZE+0.25* GRID_SIZE, y * GRID_SIZE+ 0.25*GRID_SIZE, 0.5* GRID_SIZE, 0.5*GRID_SIZE);
                painter.drawPixmap(rect, resourcePixmap);
            }
            // 可以根据其他资源代码添加更多的绘制逻辑
        }
    }

}

void gamewindow::addTool(Tool* tool, int x, int y) {
    tools.push_back(tool);
    switch (tool->getType()) {
    case ToolType::Conveyor:
        Map[y/GRID_SIZE][x/GRID_SIZE]=1;
        break;
    case ToolType::Excavator:
        if (Map[y/GRID_SIZE][x/GRID_SIZE]==-1){
            Map[y/GRID_SIZE][x/GRID_SIZE]=-3;
//            emit resourceBeingExcavated(1, x, y, tool->getRotation());
            miningElements.push_back(std::make_tuple(QPoint(x-x%GRID_SIZE+0.5*GRID_SIZE, y-y%GRID_SIZE+0.5*GRID_SIZE), 1, tool->getRotation()));
            qDebug()<<"开采 1 ing";
        }
        else if (Map[y/GRID_SIZE][x/GRID_SIZE]==-2){
            Map[y/GRID_SIZE][x/GRID_SIZE]=-4;
//            emit resourceBeingExcavated(2, x, y, tool->getRotation());
            miningElements.push_back(std::make_tuple(QPoint(x-x%GRID_SIZE+0.5*GRID_SIZE, y-y%GRID_SIZE+0.5*GRID_SIZE), 2, tool->getRotation()));
            qDebug()<<"开采 2 ing";
        }
        else{
        Map[y/GRID_SIZE][x/GRID_SIZE]=2;
        }
        break;
    case ToolType::GarbageCan:
        Map[y/GRID_SIZE][x/GRID_SIZE]=3;
        break;
    case ToolType::Cutter:
        Map[y/GRID_SIZE][x/GRID_SIZE]=4;
        if(tool->getRotation()==0){
            Map[y/GRID_SIZE][x/GRID_SIZE+1]=5;
        }
        if(tool->getRotation()==90){
            Map[y/GRID_SIZE+1][x/GRID_SIZE]=5;
        }
        if(tool->getRotation()==180){
            Map[y/GRID_SIZE][x/GRID_SIZE-1]=5;
        }
        if(tool->getRotation()==0){
            Map[y/GRID_SIZE-1][x/GRID_SIZE]=5;
        }
        break;
    default:
        break;
    }
    // 根据工具类型、位置和方向，执行相应操作
}
void gamewindow::removeTool(int x, int y) {
    for (auto it = tools.begin(); it != tools.end(); ++it) {
        Tool* tool = *it;
        if (QPoint(tool->getPosition().x()/GRID_SIZE, tool->getPosition().y()/GRID_SIZE) == QPoint(x/GRID_SIZE, y/GRID_SIZE)) {
            tools.erase(it);
            delete tool;  // 释放内存
            // 根据位置，执行相应操作
            break;
        }
    }
}
bool gamewindow::hasTool(int x, int y) const {
    for (Tool* tool : tools) {
        if (QPoint(tool->getPosition().x()/GRID_SIZE, tool->getPosition().y()/GRID_SIZE) == QPoint(x/GRID_SIZE, y/GRID_SIZE)||Map[y/GRID_SIZE][x/GRID_SIZE]==5) {
            return true;
        }
    }
    return false;
}


void gamewindow::mousePressEvent(QMouseEvent *event) {
    //删除操作
    if (event->button() == Qt::RightButton) {
        QPoint clickPos = event->pos();
        removeTool(clickPos.x(), clickPos.y());
    }

    //选中后移动残影操作
    if (event->button() == Qt::LeftButton) {
        int mouseX = event->x();
        int mouseY = event->y();

        // 绘制工具图片
        int toolSize = GRID_SIZE; // 工具图片的大小
        int toolSpacing = 50; // 工具图片之间的间距
        //  0 传送带       1 剪切器       2 开采器       3 垃圾桶
        QPoint tool0Pos(toolbarX + (toolbarWidth - toolSize * 4 - toolSpacing * 3) / 2, toolbarY + (toolbarHeight - toolSize) / 2);
        QPoint tool1Pos = tool0Pos + QPoint(toolSize + toolSpacing, 0);
        QPoint tool2Pos = tool1Pos + QPoint(toolSize * 2 + toolSpacing, 0);
        QPoint tool3Pos = tool2Pos + QPoint(toolSize + toolSpacing, 0);
        // 检查是否点击了工具栏上的工具
        if (mouseY >= toolbarY && mouseY <= toolbarY + toolbarHeight) {
            if (mouseX >= tool0Pos.x() && mouseX <= tool0Pos.x() + toolSize) {
                selectedTool = new TranslatorTool(mouseX, mouseY, 0);
            } else if (mouseX >= tool1Pos.x() && mouseX <= tool1Pos.x() + toolSize * 2) {
                selectedTool = new cutterTool(mouseX, mouseY, 0);
            } else if (mouseX >= tool2Pos.x() && mouseX <= tool2Pos.x() + toolSize) {
                selectedTool = new ExtractorTool(mouseX, mouseY, 0);
            } else if (mouseX >= tool3Pos.x() && mouseX <= tool3Pos.x() + toolSize) {
                selectedTool = new TrashTool(mouseX, mouseY, 0);
            }
            if (selectedTool) {
                selectedToolOffset=QPoint(0.5*GRID_SIZE, 0.5*GRID_SIZE);
                isMousePressed=true;
                }
        }
    }
}
void gamewindow::mouseMoveEvent(QMouseEvent *event) {
    if (selectedTool) {
        int mouseX = event->x();
        int mouseY = event->y();

        // 更新选中工具的位置
        selectedTool->getPosition() = QPoint(mouseX, mouseY);
        selectedTool->setGridPos(mouseX,mouseY);
//        update();
    }
}

void gamewindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && selectedTool) {
        int mouseX = event->x();
        int mouseY = event->y();

        // 判断是否在界面内松开鼠标
        if (!hasTool(mouseX, mouseY)&&(mouseY < toolbarY || mouseY > toolbarY + toolbarHeight ||mouseX<toolbarX ||mouseX>toolbarX+toolbarWidth)) {
            // 添加工具到界面和tools向量中
            addTool(selectedTool, mouseX, mouseY);

        } else {
            delete selectedTool;  // 释放内存
        }
        isMousePressed=false;
        selectedTool = nullptr;
        update();  // 重新绘制界面
    }
}
