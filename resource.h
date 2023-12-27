#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include "map.h"
#include "global.h"
#include <QPainter>
class resource : public QObject
{
    Q_OBJECT
    int currentX, currentY;

    int kind; // 1代表为resource1 2 代表为resource2 3 表示 resource1 被切成了 一半
    double rate = 1.0; //随传送带运行的速率
    int direction; // 行动方向
public:
    explicit resource(int kind, int x, int y, int direction): currentX(x), currentY(y), direction(direction), kind(kind){};
    void moveWithConveyor(double _rate, double cuttingRate);//direction 0 向上     90 向右     180 down      270  left  360 + specific
    void draw(QPainter&);
    int state=1;//1代表显示  0 代表不显示需要被删除  2 表示不显示不需要删除
    int getX(){
        return currentX;
    }
    int getY(){
        return currentY;
    }
    bool match1(int dir, int next);
    bool match2(int dir, int next);
signals:
    void resourceGenerated(resource* newResource);
};

#endif // RESOURCE_H
