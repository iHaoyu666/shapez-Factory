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
class gamewindow : public QWidget
{
    Q_OBJECT
public:
    explicit gamewindow(QWidget *parent = nullptr);
    void drawMap(QPainter&);            //画出地图
    void drawToolSelection(QPainter&); //画出选择框
    void drawresource(QPainter&);   //画资源
    void paintEvent(QPaintEvent* event) override; //绘画事件
//    bool eventFilter(QObject* obj, QEvent* event) override;
    void addTool(Tool* tool, int x, int y);  // 添加工具
    void removeTool(int x, int y);  // 移除工具
    bool hasTool(int x, int y) const;  // 检查是否存在工具
    QTimer *refreshTimer;
    QTimer* keyCheckTimer;
    QLabel* moneyLable = new QLabel(this);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void removeTool(const QPoint& position);  // 移除工具
    void checkRKeyPressed();
private:
    // 上一次旋转的时间戳
    QDateTime lastRotationTime;
    // 最小时间间隔（毫秒）
    int rotationInterval = 200;
    //金钱数
    int money=0;

    bool isRKeyPressed=false;
    bool isMousePressed = false;
    std::vector<resource> resources;
    std::vector<Tool*> tools;
    double conveyorRate;//传送带速率
    Tool* selectedTool = nullptr;  // 选中的工具
    QPoint selectedToolOffset;
    /*int Map[mapHeight][mapWidth]={0};*///记录地图上的数据 可以外部导入导出
    //0 表示 空    1 表示 传送带 2 表示开采器  3 表示 垃圾桶 4 表示剪切器主体头 5 表示剪切器垃圾头
    //-1 表示可开采矿物1  -2 代表可开采矿物2  -5代表交付中心 -3 表式矿物1开采中 -4表示 矿物2在开采中

//    int Map[mapHeight][mapWidth]{
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, -5, -5, -5, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, -5, -5, -5, 0, 0, 0, 0, 0},
//        {0, -2, -2, -2, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, -5, -5, -5, 0, 0, 0, 0, 0},
//        {0, -2, -2, -2, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -5, -5, -5, -5, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

//    };

signals:
    void resourceBeingExcavated(int x, int y, int angle);
};

#endif // GAMEWINDOW_H

