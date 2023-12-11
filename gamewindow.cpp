#include "gamewindow.h"
#include "config.h"
#include "tool.h"
#include "cuttertool.h"
#include "extractortool.h"
#include "trashtool.h"
#include "translatortool.h"
#include "map.h"
#include <QTimer>
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

    QPainter painter(this);
    setMouseTracking(true);
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, QOverload<>::of(&gamewindow::update));
    refreshTimer->start(10);  // 设置刷新间隔，单位为毫秒
}

void gamewindow::paintEvent(QPaintEvent* event) {

    QPainter painter(this);
    drawMap(painter);
    drawToolSelection(painter);
    if (GetKeyState('R')<0&&isMousePressed) {
        selectedTool->rotate(90);
    }
    for (const auto& tool : tools){
        tool->draw(painter);

    }



    if (selectedTool) {
        selectedTool->draw(painter);
    }
    painter.end();
}
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
//    const int toolbarWidth = GAME_WIDTH * 0.5;
//    const int toolbarHeight = 100;

//    // 工具栏的位置
//    int toolbarX = (width() - toolbarWidth) / 2;
//    int toolbarY = height() - toolbarHeight - 20; // 距离底部一定的间距

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
    int toolSize = 75; // 工具图片的大小
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


void gamewindow::addTool(Tool* tool) {
    tools.push_back(tool);
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
        if (QPoint(tool->getPosition().x()/GRID_SIZE, tool->getPosition().y()/GRID_SIZE) == QPoint(x/GRID_SIZE, y/GRID_SIZE)) {
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
        int toolSize = 75; // 工具图片的大小
        int toolSpacing = 50; // 工具图片之间的间距
        //  0 传送带       1 剪切器       2 开采器       3 垃圾桶
        QPoint tool0Pos(toolbarX + (toolbarWidth - toolSize * 4 - toolSpacing * 3) / 2, toolbarY + (toolbarHeight - toolSize) / 2);
        QPoint tool1Pos = tool0Pos + QPoint(toolSize + toolSpacing, 0);
        QPoint tool2Pos = tool1Pos + QPoint(toolSize * 2 + toolSpacing, 0);
        QPoint tool3Pos = tool2Pos + QPoint(toolSize + toolSpacing, 0);
        // 检查是否点击了工具栏上的工具
        if (mouseY >= toolbarY && mouseY <= toolbarY + toolbarHeight) {
            if (mouseX >= tool0Pos.x() && mouseX <= tool0Pos.x() + toolSize) {
                selectedTool = new TranslatorTool(0, 0, 0);
            } else if (mouseX >= tool1Pos.x() && mouseX <= tool1Pos.x() + toolSize * 2) {
                selectedTool = new cutterTool(0, 0, 0);
            } else if (mouseX >= tool2Pos.x() && mouseX <= tool2Pos.x() + toolSize) {
                selectedTool = new ExtractorTool(0, 0, 0);
            } else if (mouseX >= tool3Pos.x() && mouseX <= tool3Pos.x() + toolSize) {
                selectedTool = new TrashTool(0, 0, 0);
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
            addTool(selectedTool);
        } else {
            delete selectedTool;  // 释放内存
        }
        isMousePressed=false;
        selectedTool = nullptr;
        update();  // 重新绘制界面
    }
}
void gamewindow::handleKeyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_R && selectedTool!=nullptr) {
        selectedTool->rotate(90);
    }
    update();
}
