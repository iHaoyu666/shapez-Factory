#include "resource.h"
#include <QDebug>
#include <cmath>
void resource::draw(QPainter &painter){
    if (state==0||state==2){
        return;
    }
    QPixmap resource1Image(":/res/pic/pieces/circle1.png");
    QPixmap resource2Image(":/res/pic/pieces/res2.png");
    QPixmap resource1clipImage1(":/res/pic/pieces/circle1uphalf.png");
    QPixmap resource1clipImage2(":/res/pic/pieces/circle1downhalf.png");
    QPixmap resource1clipImage3(":/res/pic/pieces/circle1lefthalf.png");
    QPixmap resource1clipImage4(":/res/pic/pieces/circle1righthalf.png");

    switch(kind){
    case 1:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource1Image);
        break;
    case 2:
        painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.5*GRID_SIZE, resource2Image);
        break;
    case 3:
        if(chooseFlag==0){
            switch (direction)
            {
            case 0: // 向上
                pixmap = &resource1clipImage3;
                size=QSize(0.25*GRID_SIZE, 0.5*GRID_SIZE);
                pixNum=3;
//                painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.25*GRID_SIZE, 0.5*GRID_SIZE, resource1clipImage3);
                break;
            case 90: // 向右
                pixmap = &resource1clipImage1;
                size=QSize(0.5*GRID_SIZE, 0.25*GRID_SIZE);
                pixNum=1;
//                painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.25*GRID_SIZE, resource1clipImage1);
                break;
            case 180:  //向下
                pixmap = &resource1clipImage4;
                size=QSize(0.25*GRID_SIZE, 0.5*GRID_SIZE);
                pixNum=4;

//                painter.drawPixmap(currentX, currentY-0.25*GRID_SIZE, 0.25*GRID_SIZE, 0.5*GRID_SIZE, resource1clipImage4);
                break;
            case 270:  //向左
                pixmap = &resource1clipImage2;
                size=QSize(0.5*GRID_SIZE, 0.25*GRID_SIZE);
                pixNum=2;

//                painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY, 0.5*GRID_SIZE, 0.25*GRID_SIZE, resource1clipImage2);
                break;
            default:
                break;
            }
            chooseFlag=1;
            painter.drawPixmap(QRect(QPoint(currentX-5, currentY-5), size),*pixmap);
        }
        else{
            switch (pixNum) {
            case 1:
                pixmap=&resource1clipImage1;
                break;
            case 2:
                pixmap=&resource1clipImage2;
                break;
            case 3:
                pixmap=&resource1clipImage3;
                break;
            case 4:
                pixmap=&resource1clipImage4;
                break;
            default:
                break;
            }
            painter.drawPixmap(QRect(QPoint(currentX-5, currentY-5), size), *pixmap);
        }


        break;
    case 4:
        if(chooseFlag==0){
            switch (direction)
            {
            case 0: // 向上
                pixmap = &resource1clipImage4;
                size=QSize(0.25*GRID_SIZE, 0.5*GRID_SIZE);
                pixNum=4;
                //                painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.25*GRID_SIZE, 0.5*GRID_SIZE, resource1clipImage3);
                break;
            case 90: // 向右
                pixmap = &resource1clipImage2;
                size=QSize(0.5*GRID_SIZE, 0.25*GRID_SIZE);
                pixNum=2;
                //                painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY-0.25*GRID_SIZE, 0.5*GRID_SIZE, 0.25*GRID_SIZE, resource1clipImage1);
                break;
            case 180:  //向下
                pixmap = &resource1clipImage3;
                size=QSize(0.25*GRID_SIZE, 0.5*GRID_SIZE);
                pixNum=3;
                //                painter.drawPixmap(currentX, currentY-0.25*GRID_SIZE, 0.25*GRID_SIZE, 0.5*GRID_SIZE, resource1clipImage4);
                break;
            case 270:  //向左
                pixmap = &resource1clipImage1;
                size=QSize(0.5*GRID_SIZE, 0.25*GRID_SIZE);
                pixNum=1;
                //                painter.drawPixmap(currentX-0.25*GRID_SIZE, currentY, 0.5*GRID_SIZE, 0.25*GRID_SIZE, resource1clipImage2);
                break;
            default:
                break;
            }
            chooseFlag=1;
            painter.drawPixmap(QRect(QPoint(currentX-5, currentY-5), size),*pixmap);
        }
        else{
            switch (pixNum) {
            case 1:
                pixmap=&resource1clipImage1;
                break;
            case 2:
                pixmap=&resource1clipImage2;
                break;
            case 3:
                pixmap=&resource1clipImage3;
                break;
            case 4:
                pixmap=&resource1clipImage4;
                break;
            default:
                break;
            }
            painter.drawPixmap(QRect(QPoint(currentX-5, currentY-5), size), *pixmap);
        }


        break;
    }
}

void resource::moveWithConveyor(double _rate, double cuttingRate)//int direction
{
//    // 更新资源的速率和方向
//    this->direction = direction;
//    qDebug()<<currentX<<currentY;
    if(state==2){
        rate=cuttingRate;
    }else{
        rate = _rate;
    }
    // 检查传送带方向上的下一个位置是否是传送带
    int nextX = currentX;
    int nextY = currentY;
    int nextGridX=currentX/GRID_SIZE; //存储沿运动方向走到的下一个格子的位置
    int nextGirdY=currentY/GRID_SIZE;
    switch (direction)
    {
    case 0: // 向上
        nextY-=rate;
        nextGirdY--;
        break;
    case 90: // 向右
        nextX+=rate;
        nextGridX++;
        break;
    case 180:  //向下
        nextY+=rate;
        nextGirdY++;
        break;
    case 270:  //向左
        nextX-=rate;
        nextGridX--;
        break;
    case 360:
        nextX = currentX + rate;
        nextY = currentY - rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=90;
        }
        break;
    case 450:
        nextX = currentX + rate;
        nextY = currentY - rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=0;
        }
        break;
    case 540:
        nextX = currentX + rate;
        nextY = currentY + rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=180;
        }
        break;
    case 630:
        nextX = currentX + rate;
        nextY = currentY + rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=90;
        }
        break;
    case 720:
        nextX = currentX - rate;
        nextY = currentY + rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=270;
        }
        break;
    case 810:
        nextX = currentX - rate;
        nextY = currentY + rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=180;
        }
        break;
    case 900:
        nextX = currentX - rate;
        nextY = currentY - rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=0;
        }
        break;
    case 990:
        nextX = currentX - rate;
        nextY = currentY - rate;
        if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]%90!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1){
            direction=270;
        }
        break;
    default:
        break;
    }

    // 检查下一个位置是否是资源所在地段
    if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == -3||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == -4)
    {
        state=2;
        //更新位置
        currentX=nextX;
        currentY=nextY;
    }
//    else if(direction<360&&(Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=direction&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=(direction+1))){

//    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 1||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 90||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 180||Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 270)//代表0-270度
    {
        rotateFlag=0;
        state=1;
        if (direction==0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=1||direction==90&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=90||direction==180&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=180||direction==270&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=270){
            //现在和未来的传送带方向不对 并且都是基础方向

        }
        else if(direction>270&&!match1(direction,Map[nextY/GRID_SIZE][nextX/GRID_SIZE])){
            //转弯但是转过去的传送带不对

        }
        else{
            if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE]==1){
                direction=0;
            }
            else{
                direction=Map[nextY/GRID_SIZE][nextX/GRID_SIZE];
            }

            //更新位置
            currentX=nextX;
            currentY=nextY;
        }

    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] %90==0 &&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]!=0&&Map[nextY/GRID_SIZE][nextX/GRID_SIZE]>270)//代表360-990度
    {
        state=1;
        rotateFlag=0;
        if (!match2(direction,Map[nextY/GRID_SIZE][nextX/GRID_SIZE])){
            //之前是直线或转弯 碰到转弯不对应

        }
        else if(direction==Map[nextY/GRID_SIZE][nextX/GRID_SIZE]&&(currentX/GRID_SIZE!=nextX/GRID_SIZE||currentY/GRID_SIZE!=nextY/GRID_SIZE)){
            //前后都是转弯格子里面 如果这意味着有新的格子 那么不动
        }
        else{

            direction=Map[nextY/GRID_SIZE][nextX/GRID_SIZE];


            //更新位置
            currentX=nextX;
            currentY=nextY;
        }
    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 3)//下一个位置垃圾桶
    {

        state=0;
        return;
    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 4)//下一个位置剪切器剪切头
    {
        rotateFlag=0;
        if(kind==1||kind==3){
            switch (direction)
            {
            case 0: // 向上
                if (Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE+1] == 3)
                {
                    state=2;
                    currentY-= rate;
                    kind=3;    
                }
                else if(Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE+1] == 1||Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE+1] == 360||Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE+1] == 990){
                    if(kind==1){
                        qDebug()<<"signal";
                        emit cuttingResourceGenerated(4, nextX+GRID_SIZE,nextY, direction);
                    }
                    state=2;
                    currentY-= rate;
                    kind=3;


                }
                break;
            case 90: // 向右
                if (Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE+1] == 3)
                {
                    state=2;
                    currentX+=rate;
                    kind=3;
                }
                else if(Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE+1] == 90||Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE+1] == 450||Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE+1] == 540){
                    if(kind==1){
                        emit cuttingResourceGenerated(4, nextX,nextY+GRID_SIZE, direction);
                    }
                    state=2;
                    currentX+=rate;
                    kind=3;

                }
                break;
            case 180:
                if (Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE-1] == 3)
                {

                    state=2;
                    kind=3;
                    currentY+=rate;

                }
                else if(Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE-1] == 180||Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE-1] == 630||Map[nextY/GRID_SIZE+1][nextX/GRID_SIZE-1] == 720){
                    if(kind==1){
                        emit cuttingResourceGenerated(4, nextX-GRID_SIZE,nextY, direction);
                    }
                    state=2;
                    currentY+= rate;
                    kind=3;


                }
                break;
            case 270:
                if (Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE-1] == 3)
                {
                    state=2;
                    kind=3;
                    currentX-=rate;
                }
                else if(Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE-1] == 270||Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE-1] == 810||Map[nextY/GRID_SIZE-1][nextX/GRID_SIZE-1] == 900){
                    if(kind==1){
                        emit cuttingResourceGenerated(4, nextX,nextY-GRID_SIZE, direction);
                    }
                    state=2;
                    currentX-= rate;
                    kind=3;

                }
                break;
            default:
                break;
            }
        }
//        resource* newResource = new resource(this); // 创建新资源对象
//        newResource->moveWithConveyor(direction); // 设置新资源的速率和方向
//        emit resourceGenerated(newResource); // 发送资源生成信号

        // 更新地图，将新资源放置在下一个位置

    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 5&&kind==4)//下一个位置剪切器没用的口 但是是被剪切的来了
    {
        rotateFlag=0;
        currentX=nextX;
        currentY=nextY;

    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 6)//下一个位置堆叠器主体头
    {
        rotateFlag=0;
        state=2;
        currentX=nextX;
        currentY=nextY;

    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 7)//下一个位置堆叠器副头
    {
        rotateFlag=0;
        state=2;
        switch (direction){
        case 0:
            currentX=nextX-GRID_SIZE;
            break;

        case 90:
            currentY=nextY-GRID_SIZE;
            break;

        case 180:
            currentX=nextX+GRID_SIZE;
            break;

        case 270:
            currentY=nextY+GRID_SIZE;
            break;
        }
    }
    else if (Map[nextY/GRID_SIZE][nextX/GRID_SIZE] == 8)//下一个位置旋转器
    {

        state=2;
        currentX=nextX;
        currentY=nextY;
        if (rotateFlag==0){
            if(pixNum==1){
                pixNum=4;
                size=QSize(0.25*GRID_SIZE, 0.5*GRID_SIZE);
            }
            else if(pixNum==2){
                pixNum=3;
                size=QSize(0.25*GRID_SIZE, 0.5*GRID_SIZE);
            }
            else if(pixNum==3){
                pixNum=1;
                size=QSize(0.5*GRID_SIZE, 0.25*GRID_SIZE);
            }
            else if(pixNum==4){
                pixNum=2;
                size=QSize(0.5*GRID_SIZE, 0.25*GRID_SIZE);
            }
            rotateFlag=1;
        }

    }
    else if(Map[nextY/GRID_SIZE][nextX/GRID_SIZE] ==-5 )//交付中心
    {
        donePieces++;
        gold+=goldReward;
        if(kind==1){
            if (resource1Needed!=0){
                resource1Needed--;
            }
        }
        if(kind==2){
            if (resource2Needed!=0){
                resource2Needed--;
            }
        }
        if(kind==3||kind==4){
            if (resource1clipNeeded!=0){
                resource1clipNeeded--;
            }
        }
        state=0;
        return;
    }
    else
    {

    }


}

bool resource::match1(int dir, int next){
    if((dir==360||dir==630)&&next!=90){
        return false;
    }
    if((dir==450||dir==900)&&next!=1){
        return false;
    }
    if((dir==540||dir==810)&&next!=180){
        return false;
    }
    if((dir==720||dir==990)&&next!=270){
        return false;
    }
    return true;
}
bool resource::match2(int dir, int next){
    if((dir==0||dir==450||dir==900)&&next!=360&&next!=990&&next!=dir){
        qDebug()<<"1";
        return false;
    }
    if((dir==90||dir==360||dir==630)&&next!=450&&next!=540&&next!=dir){
        qDebug()<<"2";
        return false;
    }
    if((dir==180||dir==540||dir==810)&&next!=630&&next!=720&&next!=dir){
        qDebug()<<"3";
        return false;
    }
    if((dir==270||dir==720||dir==990)&&next!=810&&next!=900&&next!=dir){
        qDebug()<<"4";return false;
    }

    return true;
}
