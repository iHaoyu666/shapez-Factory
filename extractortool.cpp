#include "extractortool.h"
#include "config.h"
void ExtractorTool::draw(QPainter& painter){
    QPixmap extractorPixmap(":/res/pic/buildings/2.png");
    // 根据工具的位置和尺寸进行绘制
    painter.save();  // 保存当前绘图状态
    painter.translate(position);  // 平移坐标系到工具的位置
    painter.rotate(rotationAngle);  // 根据工具的旋转角度进行旋转

    // 在绘图设备上绘制剪切器的图片
    painter.drawPixmap(QRect(-position.x()% GRID_SIZE, -position.y()%GRID_SIZE,GRID_SIZE, GRID_SIZE), extractorPixmap);

    painter.restore();  // 恢复之前的绘图状态
}
