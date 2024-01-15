#ifndef TRASHTOOL_H
#define TRASHTOOL_H
#include "tool.h"

class TrashTool: public Tool        //垃圾桶
{
public:
    TrashTool(int x, int y, int rotation): Tool(ToolType::GarbageCan, x, y, rotation) {}
    void draw(QPainter& painter);
};

#endif // TRASHTOOL_H
