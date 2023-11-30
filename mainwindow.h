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
private:
    Ui::MainWindow *ui;

//protected:
//    void paintEvent(QPaintEvent* event);

public slots:
    void startGame();

    void loadGame();

    void showGameInfo();
};
#endif // MAINWINDOW_H
