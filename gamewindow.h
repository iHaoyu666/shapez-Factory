#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
//游戏界面
#include "tool.h"
#include <QWidget>
#include <QPainter>         //画家类
#include <QMouseEvent>      //鼠标事件
#include "resource.h"
#include <windows.h>
#include <QDebug>
#include "config.h"
#include <QDateTime>
#include <QLabel>
#include "global.h"
#include "enhancementhub.h"
#include "task.h"
#include <QPushButton>
#include "rotatetool.h"
#include <QSoundEffect>
class gamewindow : public QWidget
{
    Q_OBJECT
public:
    explicit gamewindow(QWidget *parent = nullptr);
//    ~gamewindow();
    void drawMap(QPainter&);            //画出地图
    void drawToolSelection(QPainter&); //画出选择框
    void drawresource(QPainter&);   //画资源
    void paintEvent(QPaintEvent* event) override; //绘画事件
//    bool eventFilter(QObject* obj, QEvent* event) override;
    void addTool(Tool* tool, int x, int y);  // 添加工具
    void removeTool(int x, int y);  // 移除工具
    bool hasTool(int x, int y) const;  // 检查是否存在工具
    QTimer* refreshTimer;
    QTimer* keyCheckTimer;
    QTimer* generateTimer;
    QTimer* moveTimer;
    QLabel* moneyLable = new QLabel(this);
    QLabel* centerLable = new QLabel(this);
    QLabel* resource1Lable = new QLabel(this);
    QLabel* resource2Lable = new QLabel(this);
    QLabel* resource1clipLable = new QLabel(this);
    QLabel* miningRateLabel = new QLabel(this);
    QLabel* cuttingRateLabel = new QLabel(this);
    QLabel* movingRateLabel = new QLabel(this);
    QLabel* doneLabel = new QLabel(this);
    QSoundEffect *selecttool;
    QSoundEffect *bgm;
    QSoundEffect *tooldelete;
    QSoundEffect *toolputdown;


    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void removeTool(const QPoint& position);  // 移除工具
    void removeresource(resource* res);
    void checkRKeyPressed();
    void generateResource(int kind, int x, int y, int angle);
private:
    Task* task= new Task(this);
    EnhancementHub* enhancementHub;
    // 上一次旋转的时间戳
    QDateTime lastRotationTime;
    // 最小时间间隔（毫秒）
    int rotationInterval = 125;
    int moveInterval=70;
    //金钱数
    int money=0;
    //交付数
//    int donePieces=0;
    double movingRate=1.0;//传送速度
    double miningRate=3000; //开采速度 除以1000表示秒数 用于给generateTimer参数
    double cuttingRate=1.0; //切割速度
    int flag=0;
    int warningflag=0;
    bool isRKeyPressed=false;
    bool isMousePressed = false;
    std::vector<resource*> resources;
    std::vector<Tool*> tools;
    QVector<std::tuple<QPoint, int, int>> miningElements;
    double conveyorRate;//传送带速率
    Tool* selectedTool = nullptr;  // 选中的工具
    QPoint selectedToolOffset;
    /*int Map[mapHeight][mapWidth]={0};*///记录地图上的数据 可以外部导入导出
    //0 表示 空    1 表示 传送带 2 表示开采器  3 表示 垃圾桶 4 表示剪切器主体头 5 表示剪切器垃圾头
    //-1 表示可开采矿物1  -2 代表可开采矿物2  -5代表交付中心 -3 表式矿物1开采中 -4表示 矿物2在开采中
    //6 表示堆叠器主体头    7表示堆叠器副头  8 表示顺时针旋转器
signals:
    void resourceBeingExcavated(int kind, int x, int y, int angle);
    void taskCompleted();//一个任务完成信号
    void windowclose();//窗口关闭
public slots:
    void increaseMiningRate();
    void increaseConveyorRate();
    void increaseCuttingRate();
    void showEnhancementHub();
    void askforclose();


};

#endif // GAMEWINDOW_H

