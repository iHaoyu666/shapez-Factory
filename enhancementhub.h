#ifndef ENHANCEMENTHUB_H
#define ENHANCEMENTHUB_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
class EnhancementHub : public QMainWindow       //局部强化中心类
{
    Q_OBJECT
public:
    explicit EnhancementHub(QWidget *parent = nullptr);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
signals:
    void miningRateIncreased();
    void conveyorRateIncreased();
    void cuttingRateIncreased();

private:
    QPushButton *miningButton;
    QPushButton *conveyorButton;
    QPushButton *cuttingButton;
};

#endif // ENHANCEMENTHUB_H
