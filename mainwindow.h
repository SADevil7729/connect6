#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>
#include <QTime>

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
    void count_value(int *value);
    int judge_value(int t, int flag,int space);
    void judge4(int *value);
    void judge7(int *value);
    void judge8(int *value);
    void judge9(int *value);
    void chess_center(int *value_x, int *value_y);
    int ai_place(int player, int layer,int max_value[]);
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
