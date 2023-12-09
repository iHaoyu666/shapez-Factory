#include "cuttertool.h"
#include "config.h"
void cutterTool::draw(QPainter& painter){
    QPixmap cutterPixmap(":/res/pic/buildings/1.png");
    // 根据工具的位置和尺寸进行绘制
    painter.save();  // 保存当前绘图状态
    painter.translate(position);  // 平移坐标系到工具的位置
    painter.rotate(rotationAngle);  // 根据工具的旋转角度进行旋转

    QRect rect(-position.x()% GRID_SIZE, -position.y()%GRID_SIZE, 2 * GRID_SIZE, GRID_SIZE);
    // 在绘图设备上绘制剪切器的图片
    painter.drawPixmap(rect, cutterPixmap.scaled(GRID_SIZE * 2, GRID_SIZE, Qt::KeepAspectRatio));

    painter.restore();  // 恢复之前的绘图状态


}
