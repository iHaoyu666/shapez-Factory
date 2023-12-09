#ifndef TOOL_H
#define TOOL_H
#include <QPoint>
#include <QSize>
#include <qpainter.h>
enum class ToolType {
    Conveyor,
    Cutter,
    GarbageCan,
    Excavator
};
class Tool
{
public:
    Tool(ToolType type, int x, int y, int rotation) : type(type), position(x,y), rotationAngle(rotation) {}

    void rotate(int angle) {
        rotationAngle += angle;
    }
    ToolType getType() const { return type; }
    QPoint& getPosition() { return position; }
    int getRotation() const { return rotationAngle; }
    virtual void draw(QPainter&)= 0 ;
    virtual ~Tool() {}
protected:
    QPoint position;  // 工具位置
    int rotationAngle;  // 旋转角度
    ToolType type;
};



#endif // TOOL_H
