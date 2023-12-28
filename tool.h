#ifndef TOOL_H
#define TOOL_H
#include <QPoint>
#include <QSize>
#include <qpainter.h>
#include "config.h"
enum class ToolType {
    Conveyor,
    Cutter,
    GarbageCan,
    Excavator,
    Stack,
    RotateTool
};
class Tool
{
public:
    Tool(ToolType type, int x, int y, int rotation) : type(type), position(x,y), rotationAngle(rotation) {
        XGrid=x/GRID_SIZE;
        YGrid=y/GRID_SIZE;
    }
    void rotate(int angle) {
        rotationAngle += angle;
        if (type!=ToolType::Conveyor){
            rotationAngle=rotationAngle % 360;
        }
        else{
            rotationAngle=rotationAngle % 1080;
        }
    }
    ToolType getType() const { return type; }
    QPoint& getPosition() { return position; }
    int getRotation() const { return rotationAngle; }
    virtual void draw(QPainter&)= 0 ;
    QPoint getGridPos(){return QPoint(XGrid,YGrid);}
    void setGridPos(int x, int y){XGrid=x/GRID_SIZE;YGrid=y/GRID_SIZE;}
    virtual ~Tool() {}
protected:
    QPoint position;  // 工具位置
    int rotationAngle;  // 旋转角度
    ToolType type;
    int XGrid, YGrid;
};



#endif // TOOL_H
