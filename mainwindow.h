#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
/*
#include <QSound>
#include <QSoundEffect>
#include <QMediaPlayer>
*/
#include <QTimer>
#include <QObject>
#include <QDesktopWidget>
#include <QGraphicsOpacityEffect>
#include <QGraphicsScene>
#include <QPainter>
#include <QUrl>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <QWidget>
#include <QKeyEvent>
#include <Qt>
#include <QPushButton>
#include <QList>

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
