#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>

class resource : public QObject
{
    Q_OBJECT
    int rate;
    double direction;
public:
    explicit resource(QObject *parent = nullptr);
    void moveWithConveyor(double rate, double direction);
signals:

};

#endif // RESOURCE_H
