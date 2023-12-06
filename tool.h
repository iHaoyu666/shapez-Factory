#ifndef TOOL_H
#define TOOL_H

#include <QObject>

class Tool : public QObject
{
    Q_OBJECT
public:
    explicit Tool(QObject *parent = nullptr);

signals:

};

#endif // TOOL_H
