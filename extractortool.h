#ifndef EXTRACTORTOOL_H
#define EXTRACTORTOOL_H
#include "tool.h"

class ExtractorTool: public Tool        //开采器类
{
public:
    ExtractorTool(int x, int y, int rotation): Tool(ToolType::Excavator, x, y, rotation) {}
    void draw(QPainter& painter) ;
};

#endif // EXTRACTORTOOL_H
