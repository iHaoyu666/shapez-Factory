#ifndef ENHANCEMENTHUB_H
#define ENHANCEMENTHUB_H

#include <QWidget>
#include <QPushButton>
class EnhancementHub : public QWidget
{
    Q_OBJECT
public:
    explicit EnhancementHub(QWidget *parent = nullptr);

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
