#ifndef TRANSLATORTOOL_H
#define TRANSLATORTOOL_H
#include "tool.h"

class TranslatorTool: public Tool
{
public:
    TranslatorTool(int x, int y, int rotation): Tool(ToolType::Conveyor, x, y, rotation) {}
    void draw(QPainter& painter) ;
};

#endif // TRANSLATORTOOL_H
