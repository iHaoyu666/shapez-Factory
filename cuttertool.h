#ifndef CUTTERTOOL_H
#define CUTTERTOOL_H
#include "tool.h"
#include <QKeyEvent>
class cutterTool: public Tool           //剪切器类
{
    QPoint rubbishPos;
public:
    cutterTool(int x, int y, int rotation): Tool(ToolType::Cutter, x, y, rotation) {}
    void draw(QPainter& painter) ;
};

#endif // CUTTERTOOL_H
