#include "task.h"
#include "global.h"
Task::Task(QObject *parent)
    : QObject{parent}
{

}
void Task::nextTask(){
    if (count==1){
        clean();
        resource1Needed=20;

        count=2;
    }
    else if(count==2){
        clean();
        resource2Needed=30;

        count=3;
    }
    else if(count==3)
    {
        clean();
        resource1clipNeeded=50;
        count=1;
    }

}
void Task::clean(){
    resource1Needed=0;
    resource2Needed=0;
    resource1clipNeeded=0;
}
