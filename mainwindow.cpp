#include "mainwindow.h"
#include "ui_mainwindow.h"
#define max_x 30
#define max_y 30
#define windowsize_x 1200
#define windowsize_y 800
int zoom = 50;

int zoom_center_x = 0;
int zoom_center_y = 0;
int zoom_revise_x = 0;
int zoom_revise_y = 0;
int mouse_click_x=0;
int mouse_click_y=0;
int board[max_x][max_y];
int condition=1;
int left_chess=1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int i,j;
    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            board[i][j]=0;
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::count_value(int player)
{

}
void MainWindow::ai_place(int player)
{

}
void MainWindow::paintEvent(QPaintEvent *e)
{
    int i = 0, j = 0;
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 5));
    /*
    int revise_x = 0, revise_y = 0;
    if (max_x * zoom > windowsize_x)
    {
        revise_x = zoom_center_x;
    }
    if (max_y * zoom > windowsize_y)
    {
        revise_y = zoom_center_y;
    }
    //滑鼠座標= zoom_center_x
    */


    for (i = 1; i <= max_x; i++)
    {
        painter.drawLine(i * zoom, zoom, i * zoom, max_y * zoom);
    }
    for (j = 1; j <= max_y; j++)
    {
        painter.drawLine(zoom, j * zoom, max_x * zoom, j * zoom);
    }
    painter.setPen(QPen(Qt::black, zoom*3/5));
    for (i = 1; i <= max_x; i++)
    {
        for (j = 1; j <= max_y; j++)
        {
            if (board[i][j]==1)
            {
                painter.drawPoint(zoom/2+i * zoom, zoom/2+j * zoom);
            }
        }
    }

}
void MainWindow::wheelEvent(QWheelEvent *e)
{
    if (e->delta() < 0)
    {
        if (zoom > 25)
        {
            zoom--;
        }
    }
    else if (e->delta() > 0)
    {
        if (zoom < 50)
        {
            zoom++;
        }
    }
    zoom_center_x=e->x();
    zoom_center_y=e->y();
    //printf("zoom:%d x:%d,y:%d", zoom,e->x(),e->y());
    fflush(stdout);
    this->repaint();

}
void MainWindow::mousePressEvent(QMouseEvent *e)
{

    mouse_click_x=(e->pos().x())/zoom;
    mouse_click_y=(e->pos().y())/zoom;
    printf("Press x:%d , y:%d (%d,%d)",e->pos().x(),e->pos().y(),mouse_click_x,mouse_click_y);
    fflush(stdout);
    if(condition==1&&left_chess>=1)
    {
        if(board[mouse_click_x][mouse_click_y]==0)
        {
            board[mouse_click_x][mouse_click_y]=1;
            repaint();
            left_chess--;
            if(left_chess<=0)
            {
                condition=2;
            }
        }
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    /*
    zoom_revise_x=mouse_click_x-e->pos().x();
    zoom_revise_y=mouse_click_y-e->pos().y();

    zoom_center_x+=zoom_revise_x;
    zoom_center_y+=zoom_revise_y;
    zoom_revise_x=0;
    zoom_revise_y=0;
    //printf("Move x:%d , y:%d",e->pos().x(),e->pos().y());
    //fflush(stdout);
    this->repaint();*/
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    /*
    zoom_center_x+=zoom_revise_x;
    zoom_center_y+=zoom_revise_y;
    zoom_revise_x=0;
    zoom_revise_y=0;
    printf("center x:%d , y:%d",zoom_center_x,zoom_center_y);
    fflush(stdout);
    this->repaint();
    //printf("Release x:%d , y:%d",e->pos().x(),e->pos().y());
    //fflush(stdout);
    */
}
