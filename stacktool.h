#ifndef STACKTOOL_H
#define STACKTOOL_H

#include <QWidget>
#include "tool.h"
class StackTool : public Tool       //堆叠器
{

public:
    explicit StackTool(QWidget *parent = nullptr);
    StackTool(int x, int y, int rotation): Tool(ToolType::Stack, x, y, rotation) {}
    void draw(QPainter& painter) ;
signals:

};

#endif // STACKTOOL_H
