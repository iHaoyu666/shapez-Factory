#include "trashtool.h"
#include "config.h"
void TrashTool::draw(QPainter& painter){
    QPixmap trashPixmap(":/res/pic/buildings/4.png");
    // 根据工具的位置和尺寸进行绘制
    painter.save();  // 保存当前绘图状态
    painter.translate(position);  // 平移坐标系到工具的位置
    painter.rotate(rotationAngle);  // 根据工具的旋转角度进行旋转
    QRect rect;
    int x_shift=position.x()% GRID_SIZE,y_shift=position.y()% GRID_SIZE;
    switch (rotationAngle) {
    case 0:
        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        break;
    case 90:
        rect = QRect(QPoint(-y_shift, x_shift-GRID_SIZE), QSize(GRID_SIZE,  GRID_SIZE));
        break;
    case 180:
        rect = QRect(QPoint(x_shift-GRID_SIZE, y_shift-GRID_SIZE), QSize(GRID_SIZE, GRID_SIZE));
        break;
    case 270:
        rect = QRect(QPoint(y_shift-GRID_SIZE, -x_shift), QSize(GRID_SIZE,  GRID_SIZE));
        break;
    default:
        rect = QRect(QPoint(-GRID_SIZE, -GRID_SIZE / 2), QSize(GRID_SIZE, GRID_SIZE));
        break;
    }

    // 在绘图设备上绘制剪切器的图片
    painter.drawPixmap(rect, trashPixmap);
    // 在绘图设备上绘制剪切器的图片

    painter.restore();  // 恢复之前的绘图状态
}
