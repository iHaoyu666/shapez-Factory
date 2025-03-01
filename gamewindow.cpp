#include "gamewindow.h"
#include "config.h"
#include "tool.h"
#include "cuttertool.h"
#include "extractortool.h"
#include "trashtool.h"
#include "translatortool.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include "stacktool.h"
#include <QSound>
#include <QMediaPlayer>
#include <QSoundEffect>
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
    //初始化背景音乐
    bgm=new QSoundEffect;
    bgm->setSource(QUrl::fromLocalFile(":/res/music/bgminwav.wav"));
    bgm->setLoopCount(10);  //循环次数
    bgm->setVolume(0.25f); //音量  0~1之间
    bgm->play();

    //初始化音效
    selecttool =new QSoundEffect;
    selecttool->setSource(QUrl::fromLocalFile(":/res/music/toolselect.wav"));
    selecttool->setLoopCount(1);  //循环次数
    selecttool->setVolume(0.3f); //音量  0~1之间

    tooldelete=new QSoundEffect;
    tooldelete->setSource(QUrl::fromLocalFile(":/res/music/tooldelete.wav"));
    tooldelete->setLoopCount(1);  //循环次数
    tooldelete->setVolume(0.2f); //音量  0~1之间

    toolputdown=new QSoundEffect;
    toolputdown->setSource(QUrl::fromLocalFile(":/res/music/toolputdown.wav"));
    toolputdown->setLoopCount(1);  //循环次数
    toolputdown->setVolume(0.2f); //音量  0~1之间

    //初始化窗口属性
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    setWindowTitle(GAME_TITLE);
    setMouseTracking(true);

    //添加返回主菜单按钮
    QPushButton *backButton = new QPushButton("返回主菜单",this); //返回按钮
    backButton->setGeometry(0,GAME_HEIGHT-60,120,50);
    backButton->show();
    connect(backButton, &QPushButton::clicked, this, &gamewindow::askforclose);

    QPainter painter(this);
    //初始化刷新计时器
    refreshTimer = new QTimer(this);
    refreshTimer->start(50);
    //初始化开采计时器
    generateTimer= new QTimer(this);
    generateTimer->start(miningRate);//生成资源速度
    //初始化移动计时器
    moveTimer=new QTimer(this);
    moveTimer->start(moveInterval);

    //设置移动信号
    connect(moveTimer, &QTimer::timeout, this, [&](){
    //更新资源
        for (auto res: resources){
            connect(res, &resource::cuttingResourceGenerated, this, [=](int kind, int x, int y, int direction){
                resource* newres= new resource(kind, x, y, direction);
                newres->state=2;
                resources.push_back(newres);

            });
            res->moveWithConveyor(movingRate, cuttingRate);
        }
    });

    //设置生成资源
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
    task->nextTask();//初始化任务
    //刷新时间到则重新Paint
    connect(refreshTimer, &QTimer::timeout, this, QOverload<>::of(&gamewindow::update));

    //三个速率标签
    miningRateLabel->setText("开采间隔秒数: " + QString::number(miningRate/1000.0));
    miningRateLabel->move(GAME_WIDTH-3*GRID_SIZE, GAME_HEIGHT-GRID_SIZE);
    cuttingRateLabel->setText("剪切速率: " + QString::number(cuttingRate));
    cuttingRateLabel->move(GAME_WIDTH-3*GRID_SIZE, GAME_HEIGHT-2*GRID_SIZE);
    movingRateLabel->setText("移动速率: " + QString::number(movingRate));
    movingRateLabel->move(GAME_WIDTH-3*GRID_SIZE, GAME_HEIGHT-3*GRID_SIZE);
    //金钱标签
    moneyLable->setGeometry(20, 40, 500, 50);
    moneyLable->setFont(QFont("黑体", 20));
    moneyLable->setText(QString("金币：%1").arg(money));
    moneyLable->setStyleSheet("background-color: transparent;");
    //交付数量标签
    centerLable->setGeometry(GAME_WIDTH-5*GRID_SIZE, GRID_SIZE,500,30);
    centerLable->setFont(QFont("黑体", 10));
    centerLable->setText(QString("已交付数量:%1").arg(donePieces));
    centerLable->setStyleSheet("background-color: transparent;");

    resource1Lable->setGeometry(GAME_WIDTH-5*GRID_SIZE, GRID_SIZE+20,500,30);
    resource1Lable->setFont(QFont("黑体", 10));
    resource1Lable->setText(QString("圆形未交付数量：%1").arg(resource1Needed));
    resource1Lable->setStyleSheet("background-color: transparent;");

    resource2Lable->setGeometry(GAME_WIDTH-5*GRID_SIZE, GRID_SIZE+40,500,30);
    resource2Lable->setFont(QFont("黑体", 10));
    resource2Lable->setText(QString("方形未交付数量：%1").arg(resource2Needed));
    resource2Lable->setStyleSheet("background-color: transparent;");

    resource1clipLable->setGeometry(GAME_WIDTH-5*GRID_SIZE, GRID_SIZE+60,500,30);
    resource1clipLable->setFont(QFont("黑体", 10));
    resource1clipLable->setText(QString("半圆未交付数量：%1").arg(resource1clipNeeded));
    resource1clipLable->setStyleSheet("background-color: transparent;");

    doneLabel->setFont(QFont("黑体", 10));
    doneLabel->setGeometry(GAME_WIDTH-5*GRID_SIZE, GRID_SIZE+80, 500, 30);
    doneLabel->setText(QString("共交付数量：%1").arg(donePieces));
    doneLabel->setStyleSheet("background-color: transparent;");

    enhancementHub = new EnhancementHub(this);
    connect(this, &gamewindow::taskCompleted, this, &gamewindow::showEnhancementHub);
    // 连接EnhancementHub窗口的信号到GameWindow的槽函数
    connect(enhancementHub, &EnhancementHub::miningRateIncreased, this, &gamewindow::increaseMiningRate);
    connect(enhancementHub, &EnhancementHub::conveyorRateIncreased, this, &gamewindow::increaseConveyorRate);
    connect(enhancementHub, &EnhancementHub::cuttingRateIncreased, this, &gamewindow::increaseCuttingRate);


    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int resourceCode = Map[y][x];
            if (resourceCode == 1){
                Tool* newtool = new TranslatorTool(x*GRID_SIZE, y* GRID_SIZE,0);
                tools.push_back(newtool);
            }else if (resourceCode!=0&&resourceCode%90==0){
                Tool* newtool = new TranslatorTool(x*GRID_SIZE, y* GRID_SIZE,resourceCode);
                tools.push_back(newtool);
            }
            // 可以根据其他资源代码添加更多的绘制逻辑
        }
    }
}

void gamewindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    drawMap(painter);
    drawToolSelection(painter);
    drawresource(painter);
    moneyLable->setText(QString("金钱：%1").arg(gold));
    centerLable->setText(QString("任务%1").arg(task->getCnt()));
    resource1Lable->setText(QString("圆形未交付数量：%1").arg(resource1Needed));
    resource2Lable->setText(QString("方形未交付数量：%1").arg(resource2Needed));
    resource1clipLable->setText(QString("半圆未交付数量：%1").arg(resource1clipNeeded));
    doneLabel->setText(QString("共交付数量：%1").arg(donePieces));
    if (GetKeyState('R')<0&&isMousePressed) {
        QDateTime currentTime = QDateTime::currentDateTime();
        if (lastRotationTime.isNull() || lastRotationTime.msecsTo(currentTime) >= rotationInterval) {
            selectedTool->rotate(90);
            lastRotationTime = currentTime;
        }
    }

    for (const auto& tool : tools){//画出所有工具
        tool->draw(painter);
    }
    for (auto resource: resources){//更新资源


        if(resource->state==0){
            removeresource(resource);
            delete resource;
            continue;
        }
        resource->draw(painter);
        flag=1;
    }
    if (resource1Needed==0&&resource1clipNeeded==0&&resource2Needed==0&&flag!=0){
        enhancementHub->show();
        task->nextTask();//切换到下一个任务
        qDebug()<<"任务完成";
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

    }

void gamewindow::drawMap(QPainter& painter){
    // 设置背景颜色为浅灰色
    this->setStyleSheet("background-color: rgb(240, 240, 240);");
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
    QPixmap deliveryCenterPixmapbig(":/res/pic/buildings/3.png");
    QPixmap deliveryCenterPixmapsmall(":/res/pic/buildings/3-0.png");
    // 计算交付中心的位置
    int centerX = width() / 2 - deliveryCenterLevel* gridSize -10;
    int centerY = height() / 2 - deliveryCenterLevel* gridSize -10;

    // 绘制交付中心图片
    if(deliveryCenterLevel==1){
        QRect deliveryCenterRect(centerX, centerY, gridSize * 2+20, gridSize * 2+20);
        painter.drawPixmap(deliveryCenterRect, deliveryCenterPixmapsmall);
    }
    else{
        QRect deliveryCenterRect(centerX, centerY, gridSize * 4+20, gridSize * 4+20);
        painter.drawPixmap(deliveryCenterRect, deliveryCenterPixmapbig);
    }



}

void gamewindow::drawToolSelection(QPainter& painter){

    // 加载工具图片
    QPixmap ConveyorPixmap(":/res/pic/buildings/0-3.png");
    QPixmap CutterPixmap(":/res/pic/buildings/1.png");
    QPixmap ExcavatorPixmap(":/res/pic/buildings/2.png");
    QPixmap GarbageCanPixmap(":/res/pic/buildings/4.png");
    QPixmap StackPixmap(":/res/pic/buildings/StackTool.png");
    QPixmap RotatePixmap(":/res/pic/buildings/RotateTool.png");
    QColor toolbarColor(128, 128, 128, 128);
    // 绘制工具栏背景
    painter.setBrush(toolbarColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(toolbarX, toolbarY, toolbarWidth, toolbarHeight);

    // 绘制工具图片
    int toolSize = GRID_SIZE; // 工具图片的大小
    int toolSpacing = 50; // 工具图片之间的间距
    //  0 传送带       1 剪切器       2 开采器       3 垃圾桶  4  叠加器     5  顺时针旋转器
    QPoint tool0Pos(toolbarX + (toolbarWidth - toolSize * 6 - toolSpacing * 5) / 2, toolbarY + (toolbarHeight - toolSize) / 2);
    QPoint tool1Pos = tool0Pos + QPoint(toolSize + toolSpacing, 0);
    QPoint tool2Pos = tool1Pos + QPoint(toolSize * 2 + toolSpacing, 0);
    QPoint tool3Pos = tool2Pos + QPoint(toolSize + toolSpacing, 0);
    QPoint tool4Pos = tool3Pos + QPoint(toolSize + toolSpacing, 0);
    QPoint tool5Pos = tool4Pos + QPoint(toolSize * 2 + toolSpacing, 0);
    painter.drawPixmap(tool0Pos, ConveyorPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool1Pos, CutterPixmap.scaled(toolSize * 2, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool2Pos, ExcavatorPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool3Pos, GarbageCanPixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool4Pos, StackPixmap.scaled(toolSize*2, toolSize, Qt::KeepAspectRatio));
    painter.drawPixmap(tool5Pos, RotatePixmap.scaled(toolSize, toolSize, Qt::KeepAspectRatio));
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
                QRect rect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
                painter.drawPixmap(rect, resourcePixmap);
            }
            // 可以根据其他资源代码添加更多的绘制逻辑
        }
    }

}

void gamewindow::addTool(Tool* tool, int x, int y) {    //添加工具
    if(tool->getType()!=ToolType::Excavator && Map[y/GRID_SIZE][x/GRID_SIZE]<0){
        return;
    }
    tools.push_back(tool);
    toolputdown->play();
    switch (tool->getType()) {
    case ToolType::Conveyor:
        if(tool->getRotation()==0){
            Map[y/GRID_SIZE][x/GRID_SIZE]=1;//表示直线向上的传送带并且与0区分开
        }

        else{
            Map[y/GRID_SIZE][x/GRID_SIZE]=tool->getRotation();
        }
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
        if(tool->getRotation()==270){
            Map[y/GRID_SIZE-1][x/GRID_SIZE]=5;
        }
        break;
    case ToolType::Stack:
        Map[y/GRID_SIZE][x/GRID_SIZE]=6;
        if(tool->getRotation()==0){
            Map[y/GRID_SIZE][x/GRID_SIZE+1]=7;
        }
        if(tool->getRotation()==90){
            Map[y/GRID_SIZE+1][x/GRID_SIZE]=7;
        }
        if(tool->getRotation()==180){
            Map[y/GRID_SIZE][x/GRID_SIZE-1]=7;
        }
        if(tool->getRotation()==270){
            Map[y/GRID_SIZE-1][x/GRID_SIZE]=7;
        }
        break;
    case ToolType::RotateTool:
        Map[y/GRID_SIZE][x/GRID_SIZE]=8;
        break;
    default:
        break;
    }
    // 根据工具类型、位置和方向，执行相应操作
}
void gamewindow::removeTool(int x, int y) {     //移除工具
    for (auto it = tools.begin(); it != tools.end(); ++it) {
        Tool* tool = *it;
        if (QPoint(tool->getPosition().x()/GRID_SIZE, tool->getPosition().y()/GRID_SIZE) == QPoint(x/GRID_SIZE, y/GRID_SIZE)) {
            if(tool->getType()!=ToolType::Excavator)
            {
                Map[y/GRID_SIZE][x/GRID_SIZE]=0;
                if(tool->getType()==ToolType::Conveyor){//如果是传送带 把上面东西删了
                    for(resource* res:resources){
                        if (res->getX()/GRID_SIZE==x/GRID_SIZE&&res->getY()/GRID_SIZE==y/GRID_SIZE){
                            res->state=0;
                        }
                    }
                }
            }
            else{//开采器则需要保留原来的东西 并且这个位置不再开始生成
                Map[y/GRID_SIZE][x/GRID_SIZE]=Map[y/GRID_SIZE][x/GRID_SIZE]+2;
                for(resource* res:resources){//如果开采器上面有生成的
                    if (res->getX()/GRID_SIZE==x/GRID_SIZE&&res->getY()/GRID_SIZE==y/GRID_SIZE){
                        res->state=0;
                    }
                }
                miningElements.erase(std::remove(miningElements.begin(),miningElements.end(),
                                                 std::make_tuple(QPoint(x-x%GRID_SIZE+0.5*GRID_SIZE, y-y%GRID_SIZE+0.5*GRID_SIZE), Map[y/GRID_SIZE][x/GRID_SIZE]*(-1), tool->getRotation())),miningElements.end());
            }
            tools.erase(it);
            tooldelete->play();
            delete tool;  // 释放内存
            // 根据位置，执行相应操作
            break;
        }
    }
}
void gamewindow::removeresource(resource* res){     //移除资源
    auto it = std::find(resources.begin(), resources.end(), res);

    // 如果找到了指针，则删除它
    if (it != resources.end()) {
        resources.erase(it);
    }
}
bool gamewindow::hasTool(int x, int y) const {      //判断是否有工具在此处
    for (Tool* tool : tools) {
        if (QPoint(tool->getPosition().x()/GRID_SIZE, tool->getPosition().y()/GRID_SIZE) == QPoint(x/GRID_SIZE, y/GRID_SIZE)||Map[y/GRID_SIZE][x/GRID_SIZE]==5||Map[y/GRID_SIZE][x/GRID_SIZE]==7) {
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
        //  0 传送带       1 剪切器       2 开采器       3 垃圾桶   4  堆叠器
        QPoint tool0Pos(toolbarX + (toolbarWidth - toolSize * 6 - toolSpacing * 5) / 2, toolbarY + (toolbarHeight - toolSize) / 2);
        QPoint tool1Pos = tool0Pos + QPoint(toolSize + toolSpacing, 0);
        QPoint tool2Pos = tool1Pos + QPoint(toolSize * 2 + toolSpacing, 0);
        QPoint tool3Pos = tool2Pos + QPoint(toolSize + toolSpacing, 0);
        QPoint tool4Pos = tool3Pos + QPoint(toolSize + toolSpacing, 0);
        QPoint tool5Pos = tool4Pos + QPoint(toolSize * 2 + toolSpacing, 0);
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
            }else if (mouseX >= tool4Pos.x() && mouseX <= tool4Pos.x() + toolSize * 2) {
                selectedTool = new StackTool(mouseX, mouseY, 0);
            }
            else if (mouseX >= tool5Pos.x() && mouseX <= tool5Pos.x() + toolSize) {
                selectedTool = new RotateTool(mouseX, mouseY, 0);
            }



            if (selectedTool) {
                selecttool->play();
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

        if (GetKeyState('F')<0&&isMousePressed&&selectedTool->getType()==ToolType::Conveyor){
                Tool* newtool=new TranslatorTool(mouseX,mouseY,selectedTool->getRotation());
                if(!hasTool(mouseX,mouseY)){
                    addTool(newtool,mouseX, mouseY);
                }
                else{
                    delete newtool;
                }
        }
    }
}

void gamewindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && selectedTool) {
        int mouseX = event->x();
        int mouseY = event->y();

        // 判断是否在界面内松开鼠标
        if (!hasTool(mouseX, mouseY)&&(mouseY < toolbarY || mouseY > toolbarY + toolbarHeight ||mouseX<toolbarX ||mouseX>toolbarX+toolbarWidth)&&Map[mouseY/GRID_SIZE][mouseX/GRID_SIZE]!=-5) {
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

void gamewindow::increaseMiningRate()
{
    miningRate/=1.2;
    generateTimer->setInterval(miningRate);
    enhancementHub->hide();
    miningRateLabel->setText("开采间隔秒数: " + QString::number(miningRate/1000.0));

}

void gamewindow::increaseConveyorRate()
{
    movingRate+=1;
    enhancementHub->hide();
    movingRateLabel->setText("移动速率: " + QString::number(movingRate));
}

void gamewindow::increaseCuttingRate()
{
    cuttingRate+=1;
    enhancementHub->hide();

    cuttingRateLabel->setText("剪切速率: " + QString::number(cuttingRate));

}
void gamewindow::showEnhancementHub()
{
    // 显示EnhancementHub窗口
    enhancementHub->show();
}
void gamewindow::askforclose(){
    // 显示询问对话框
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "提醒", "你确定要返回主菜单吗？你的局部属性将重置，但你的金币将保留", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    // 根据用户选择来决定是否关闭窗口
    if (reply == QMessageBox::Yes) {        //决定关闭后 开始善后工作 这里相当于做析构函数
        for(Tool* tool:tools){
            switch(tool->getType()){
//            case ToolType::Conveyor:
//                Map[tool->getGridPos().y()][tool->getGridPos().x()]=0;
//                break;
            case ToolType::Cutter:
                Map[tool->getGridPos().y()][tool->getGridPos().x()]=0;
                if(tool->getRotation()==0){
                    Map[tool->getGridPos().y()][tool->getGridPos().x()+1]=0;
                }
                if(tool->getRotation()==90){
                    Map[tool->getGridPos().y()+1][tool->getGridPos().x()]=0;
                }
                if(tool->getRotation()==180){
                    Map[tool->getGridPos().y()][tool->getGridPos().x()-1]=0;
                }
                if(tool->getRotation()==270){
                    Map[tool->getGridPos().y()-1][tool->getGridPos().x()]=0;
                }
                break;
            case ToolType::Excavator:
                if(Map[tool->getGridPos().y()][tool->getGridPos().x()]==-3||Map[tool->getGridPos().y()][tool->getGridPos().x()]==-4){
                    Map[tool->getGridPos().y()][tool->getGridPos().x()]+=2;
                }
                else{
                    Map[tool->getGridPos().y()][tool->getGridPos().x()]=0;
                }
                break;
            case ToolType::GarbageCan:
                Map[tool->getGridPos().y()][tool->getGridPos().x()]=0;
                break;
            case ToolType::Stack:
                Map[tool->getGridPos().y()][tool->getGridPos().x()]=0;
                if(tool->getRotation()==0){
                    Map[tool->getGridPos().y()][tool->getGridPos().x()+1]=0;
                }
                if(tool->getRotation()==90){
                    Map[tool->getGridPos().y()+1][tool->getGridPos().x()]=0;
                }
                if(tool->getRotation()==180){
                    Map[tool->getGridPos().y()][tool->getGridPos().x()-1]=0;
                }
                if(tool->getRotation()==270){
                    Map[tool->getGridPos().y()-1][tool->getGridPos().x()]=0;
                }
                break;
            case ToolType::RotateTool:
                Map[tool->getGridPos().y()][tool->getGridPos().x()]=0;
                break;
            default:
                break;
            }


            delete tool;

        }
        for(resource* res:resources){       //归还资源
            delete res;
        }
        delete bgm;
        emit windowclose();
        this->deleteLater();
    }

}
