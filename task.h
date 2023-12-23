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
signals:
private:
    int count=1;//代表第几个任务
};

#endif // TASK_H
