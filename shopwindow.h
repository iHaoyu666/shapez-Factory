#ifndef SHOPWINDOW_H
#define SHOPWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class ShopWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ShopWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent* e);
public slots:
    void upgradeDeliveryCenter();
    void upgradeMiningSite();
    void upgradeGoldReward();

private:
    QLabel *coinLabel;
    QLabel *deliveryCenterLabel;
    QLabel *miningSiteLabel;
    QLabel *goldRewardLabel;

    QPushButton *deliveryCenterButton;
    QPushButton *miningSiteButton;
    QPushButton *goldRewardButton;

signals:
    void addNewResource(int x, int y);
    void closewindow();
};

#endif // SHOPWINDOW_H
