#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//主菜单界面
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initScene();
    void newgameclean();
private:
    Ui::MainWindow *ui;
    std::vector<QPoint> points;
//protected:
//    void paintEvent(QPaintEvent* event);

public slots:
    void startGame();       //新游戏

    void loadGame();        //读取存档

    void showGameInfo();

    void openShop();

    void saveData();    //保存游戏

//    void loadData();    //读取存档
};
#endif // MAINWINDOW_H
