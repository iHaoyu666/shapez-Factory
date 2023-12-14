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
    int kind;// 1代表为resource1 2 代表为resource2 3 表示 resource2 被切成了
    int rate = 1; //随传送带运行的速率
    int direction; // 行动方向
public:
    explicit resource(int kind, int x, int y, int direction): currentX(x), currentY(y), direction(direction), kind(kind){};
    void moveWithConveyor();//direction 0 向上     90 向右     180 down      270  left
    void draw(QPainter&);
signals:
    void resourceGenerated(resource* newResource);
};

#endif // RESOURCE_H
