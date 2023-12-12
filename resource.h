#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include "map.h"
#include "global.h"
class resource : public QObject
{
    Q_OBJECT
    int currentX, currentY;
    int kind;// 1代表为resource1 2 代表为resource2
    int rate = 5; //随传送带运行的速率
    int direction; // 行动方向
public:
    explicit resource(int x, int y, int direction, QObject *parent = nullptr);
    void moveWithConveyor(double rate, int direction);//direction 0 向上 90 向右
    void draw();
signals:
    void resourceGenerated(resource* newResource);
};

#endif // RESOURCE_H
