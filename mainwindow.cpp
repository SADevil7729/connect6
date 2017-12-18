#include "mainwindow.h"
#include "ui_mainwindow.h"
#define max_x 59
#define max_y 39
#define windowsize_x 1200
#define windowsize_y 800
int zoom=40;
int zoom_center_x=600;
int zoom_center_y=400;
int board[max_x][max_y];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *e)
{
   int i=0,j=0;
QPainter painter(this);
painter.setPen(QPen(Qt::red, 5));
for(i=1;i<=max_x;i++)
{
   painter.drawLine(i*zoom,0,i*zoom,windowsize_y);
}
for(j=1;j<=max_y;j++)
{
    painter.drawLine(0,j*zoom,windowsize_x,j*zoom);
}

}
void MainWindow::wheelEvent(QWheelEvent *e)
{
    if(e->delta()<0)
    {
        if(zoom>20)
        {
            zoom--;
        }
    }
    else if(e->delta()>0)
    {
        if(zoom<40)
        {
            zoom++;
        }
    }
printf("%d",zoom);
fflush(stdout);
this->repaint();

}
