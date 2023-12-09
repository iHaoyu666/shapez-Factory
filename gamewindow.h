#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
//游戏界面
#include "tool.h"
#include <QWidget>
#include <QPainter>         //画家类
#include <QMouseEvent>      //鼠标事件
#include "toolselection.h" //选择框
#include "resource.h"

class gamewindow : public QWidget
{
    Q_OBJECT
public:
    explicit gamewindow(QWidget *parent = nullptr);
    void drawMap(QPainter&);            //画出地图
    void drawToolSelection(QPainter&); //画出选择框
    void paintEvent(QPaintEvent* event) override; //绘画事件

    void addTool(Tool* tool);  // 添加工具
    void removeTool(int x, int y);  // 移除工具
    bool hasTool(int x, int y) const;  // 检查是否存在工具
    QTimer *refreshTimer;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void removeTool(const QPoint& position);  // 移除工具

    void handleKeyPressEvent(QKeyEvent* event);
private:
    std::vector<resource> resources;
    std::vector<Tool*> tools;
    double conveyorRate;//传送带速率
    Tool* selectedTool = nullptr;  // 选中的工具
    QPoint selectedToolOffset;
};

#endif // GAMEWINDOW_H

