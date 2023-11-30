#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
//游戏界面
#include <QWidget>
#include <QPainter>         //画家类
#include <QMouseEvent>      //鼠标事件
#include "toolselection.h" //选择框
class gamewindow : public QWidget
{
    Q_OBJECT
public:

    explicit gamewindow(QWidget *parent = nullptr);
    void initScene();       //初始化窗口与标题
    void drawMap(QPainter&);            //画出地图
    void drawToolSelection(QPainter&); //画出选择框
    void wheelEvent(QWheelEvent* event);
    void paintEvent(QPaintEvent* event); //绘画事件
};

#endif // GAMEWINDOW_H
