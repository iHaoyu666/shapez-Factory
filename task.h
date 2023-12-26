#ifndef TASK_H
#define TASK_H

#include <QObject>

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);

    void nextTask();
    void clean();
    int getCnt() const{
        return count;
    }
signals:
private:
    int count=0;//代表第几个任务
};

#endif // TASK_H
