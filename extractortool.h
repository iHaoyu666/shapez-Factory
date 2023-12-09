#ifndef EXTRACTORTOOL_H
#define EXTRACTORTOOL_H
#include "tool.h"

class ExtractorTool: public Tool
{
public:
    ExtractorTool(int x, int y, int rotation): Tool(ToolType::Excavator, x, y, rotation) {}
    void draw(QPainter& painter) ;
};

#endif // EXTRACTORTOOL_H
