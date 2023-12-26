#include "task.h"
#include "global.h"
Task::Task(QObject *parent)
    : QObject{parent}
{

}
void Task::nextTask(){
    if (count==0){
        clean();
        resource1Needed=20;

        count=1;
    }
    else if(count==1){
        clean();
        resource2Needed=30;

        count=2;
    }
    else if(count==2)
    {
        clean();
        resource1clipNeeded=50;
        count=0;
    }

}
void Task::clean(){
    resource1Needed=0;
    resource2Needed=0;
    resource1clipNeeded=0;
}
