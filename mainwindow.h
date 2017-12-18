#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    protected:
    void paintEvent(QPaintEvent *e);
    void wheelEvent(QWheelEvent *e);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
