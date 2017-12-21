#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int count_value(int player, int x1, int y1, int x2, int y2);
    int judge_value(int t, int flag);
    int judge1(int value,int player,int x,int y);
    int judge2(int value,int player,int x,int y);
    int judge3(int value,int player,int x,int y);
    int judge4(int value,int player,int x,int y);
    int judge6(int value,int player,int x,int y);
    int judge7(int value,int player,int x,int y);
    int judge8(int value,int player,int x,int y);
    int judge9(int value,int player,int x,int y);
    void ai_place(int player);
protected:
    void paintEvent(QPaintEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
