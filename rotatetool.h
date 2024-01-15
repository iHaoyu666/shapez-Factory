#ifndef ROTATETOOL_H
#define ROTATETOOL_H
#include "tool.h"

class RotateTool: public Tool       //旋转器类
{
public:
    RotateTool(int x, int y, int rotation): Tool(ToolType::RotateTool, x, y, rotation) {}
    void draw(QPainter& painter) ;
};

#endif // ROTATETOOL_H
