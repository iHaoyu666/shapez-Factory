#include "translatortool.h"
#include "config.h"
void TranslatorTool::draw(QPainter& painter){
    QPixmap translatorPixmap1(":/res/pic/buildings/0-3.png");
    QPixmap conveyor360(":/res/pic/buildings/0-360.png");
    QPixmap conveyor450(":/res/pic/buildings/0-450.png");
    QPixmap conveyor540(":/res/pic/buildings/0-540.png");
    QPixmap conveyor630(":/res/pic/buildings/0-630.png");
    QPixmap conveyor720(":/res/pic/buildings/0-720.png");
    QPixmap conveyor810(":/res/pic/buildings/0-810.png");
    QPixmap conveyor900(":/res/pic/buildings/0-900.png");
    QPixmap conveyor990(":/res/pic/buildings/0-990.png");
    // 根据工具的位置和尺寸进行绘制
    painter.save();  // 保存当前绘图状态
    painter.translate(position);  // 平移坐标系到工具的位置
    if (rotationAngle<360){
        painter.rotate(rotationAngle);  // 根据工具的旋转角度进行旋转
    }

    QRect rect;
    int x_shift=position.x()% GRID_SIZE,y_shift=position.y()% GRID_SIZE;
    switch (rotationAngle) {
    case 0:
        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, translatorPixmap1);
        break;
    case 90:
        rect = QRect(QPoint(-y_shift, x_shift-GRID_SIZE), QSize(GRID_SIZE,  GRID_SIZE));
        painter.drawPixmap(rect, translatorPixmap1);
        break;
    case 180:
        rect = QRect(QPoint(x_shift-GRID_SIZE, y_shift-GRID_SIZE), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, translatorPixmap1);
        break;
    case 270:
        rect = QRect(QPoint(y_shift-GRID_SIZE, -x_shift), QSize(GRID_SIZE,  GRID_SIZE));
        painter.drawPixmap(rect, translatorPixmap1);
        break;
    case 360:
        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor360);
        break;
    case 450:
        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor450);
        break;
    case 540:
        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor540);
        break;
    case 630:
        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor630);
        break;
    case 720:

        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor720);
        break;
    case 810:

        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor810);
        break;
    case 900:

        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor900);
        break;
    case 990:

        rect = QRect(QPoint(-x_shift,-y_shift), QSize(GRID_SIZE, GRID_SIZE));
        painter.drawPixmap(rect, conveyor990);
        break;

    default:
        rect = QRect(QPoint(-GRID_SIZE, -GRID_SIZE / 2), QSize(GRID_SIZE, GRID_SIZE));
        break;
    }

    // 在绘图设备上绘制剪切器的图片

    // 在绘图设备上绘制剪切器的图片

    painter.restore();  // 恢复之前的绘图状态
}
