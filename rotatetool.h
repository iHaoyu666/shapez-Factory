#ifndef ROTATETOOL_H
#define ROTATETOOL_H
#include "tool.h"

class RotateTool: public Tool
{
public:
    RotateTool(int x, int y, int rotation): Tool(ToolType::RotateTool, x, y, rotation) {}
    void draw(QPainter& painter) ;
};

#endif // ROTATETOOL_H
