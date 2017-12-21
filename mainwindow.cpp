#include "mainwindow.h"
#include "ui_mainwindow.h"
#define max_x 19
#define max_y 19
#define windowsize_x 1200
#define windowsize_y 800
int zoom = 50;

int zoom_center_x = 0;
int zoom_center_y = 0;
int zoom_revise_x = 0;
int zoom_revise_y = 0;
int mouse_click_x=0;
int mouse_click_y=0;
int flag1,flag2,flag3,flag4;
int ai_x1;
int ai_x2;
int ai_y1;
int ai_y2;
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
    }/*
    board[9][10]=1;
    board[9][11]=1;
    board[9][12]=1;
    printf("%d",count_value(1,9,9,9,13));*/
    fflush(stdout);
}


MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::judge7(int value, int player, int x, int y)//   left top
{
    if(x-1>=1&&y-1>=1)
    {
        if(board[x-1][y-1]==player)
        {
            value=judge7(value+1,player,x-1,y-1);
        }
        else if(board[x-1][y-1]!=0)
        {
            flag1++;
        }
    }
    else
    {
        flag1++;
    }
    return value;
}
int MainWindow::judge3(int value, int player, int x, int y)//   right down
{
    if(x+1<=max_x&&y+1<=max_y)
    {
        if(board[x+1][y+1]==player)
        {
            value=judge3(value+1,player,x+1,y+1);
        }
        else if(board[x+1][y+1]!=0)
        {
            flag1++;
        }
    }
    else
    {
        flag1++;
    }

    return value;
}
int MainWindow::judge8(int value, int player, int x, int y)//   top
{
    if(y-1>=1)
    {
        if(board[x][y-1]==player)
        {
            value=judge8(value+1,player,x,y-1);
        }
        else if(board[x][y-1]!=0)
        {
            flag2++;
        }
    }
    else
    {
        flag2++;
    }
    return value;
}
int MainWindow::judge2(int value, int player, int x, int y)//   down
{
    if(y+1<=max_y)
    {
        if(board[x][y+1]==player)
        {
            value=judge2(value+1,player,x,y+1);
        }
        else if(board[x][y+1]!=0)
        {
            flag2++;
        }
    }
    else
    {
        flag2++;
    }
    return value;
}
int MainWindow::judge9(int value, int player, int x, int y)//   '/'
{
    if(x+1<=max_x&&y-1>=1)
    {
        if(board[x+1][y-1]==player)
        {
            value=judge9(value+1,player,x+1,y-1);
        }
        else if(board[x+1][y-1]!=0)
        {
            flag3++;
        }
    }
    else
    {
        flag3++;
    }
    return value;
}
int MainWindow::judge1(int value, int player, int x, int y)//   '/'
{
    if(x-1>=1&&y+1<=max_y)
    {
        if(board[x-1][y+1]==player)
        {
            value=judge1(value+1,player,x-1,y+1);
        }
        else if(board[x-1][y+1]!=0)
        {
            flag3++;
        }
    }
    else
    {
        flag3++;
    }
    return value;
}
int MainWindow::judge4(int value, int player, int x, int y)//   left
{
    if(x-1>=1)
    {
        if(board[x-1][y]==player)
        {
            value=judge4(value+1,player,x-1,y);
        }
        else if(board[x-1][y]!=0)
        {
            flag4++;
        }
    }
    else
    {
        flag4++;
    }
    return value;
}

int MainWindow::judge6(int value, int player, int x, int y)//   right
{
    if(x+1<=max_x)
    {
        if(board[x+1][y]==player)
        {
            value=judge6(value+1,player,x+1,y);
        }
        else if(board[x+1][y]!=0)
        {
            flag4++;
        }
    }
    else
    {
        flag4++;
    }
    return value;
}
int MainWindow::judge_value(int t,int flag)
{
    int table[7][3]= {0,0,0
                      ,10,5,1
                      ,50,20,2
                      ,100,90,5
                      ,1000,150,20
                      ,3000,1500,30
                      ,1000000,1000000,1000000
                     };
    if(t>=6)
    {
        return 10000000;
    }
    return table[t][flag];
}
int MainWindow::count_value(int player,int x1,int y1,int x2,int y2)
{

    board[x1][y1]=player;
    board[x2][y2]=player;
    int t=0;
    int value=0;
    flag1=0;
    flag2=0;
    flag3=0;
    flag4=0;

    t=judge7(0,player,x1,y1)+judge3(0,player,x1,y1)+1;
    value+=judge_value(t,flag1);

    t=judge8(0,player,x1,y1)+judge2(0,player,x1,y1)+1;
    value+=judge_value(t,flag2);

    t=judge9(0,player,x1,y1)+judge1(0,player,x1,y1)+1;
    value+=judge_value(t,flag3);

    t=judge4(0,player,x1,y1)+judge6(0,player,x1,y1)+1;
    value+=judge_value(t,flag4);



    flag1=0;
    flag2=0;
    flag3=0;
    flag4=0;

    t=judge7(0,player,x2,y2)+judge3(0,player,x2,y2)+1;
    value+=judge_value(t,flag1);
    t=judge8(0,player,x2,y2)+judge2(0,player,x2,y2)+1;
    value+=judge_value(t,flag2);
    t=judge9(0,player,x2,y2)+judge1(0,player,x2,y2)+1;
    value+=judge_value(t,flag3);
    t=judge4(0,player,x2,y2)+judge6(0,player,x2,x2)+1;
    value+=judge_value(t,flag4);




    board[x1][y1]=0;
    board[x2][y2]=0;
    return value;



}
void MainWindow::ai_place(int player)
{
    int i,j,k,l;
    int max_value=0;
    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            if(board[i][j]==0)
            {
                for(k=1; k<=max_x; k++)
                {
                    for(l=1; l<=max_y; l++)
                    {
                        if(board[k][l]==0)//empty
                        {
                            if(i==k&&j==l)
                            {
                                continue;
                            }
                            else
                            {
                                int temp=count_value(1,i,j,k,l);
                                int temp2=count_value(2,i,j,k,l);
                                temp+=temp2;
                                if(temp>=500)
                                {
                                    printf("value:%d x1:%d y1:%d x2:%d y2:%d\n",temp,i,j,k,l);
                                    fflush(stdout);
                                }
                                if(temp>max_value)
                                {
                                    ai_x1=i;
                                    ai_y1=j;
                                    ai_x2=k;
                                    ai_y2=l;
                                    max_value=temp;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    repaint();
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
    painter.setPen(QPen(Qt::yellow, zoom*3/5));
    for (i = 1; i <= max_x; i++)
    {
        for (j = 1; j <= max_y; j++)
        {
            if (board[i][j]==2)
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
        //printf("Press x:%d , y:%d (%d,%d) condition:%d player:%d left_chess:%d",e->pos().x(),e->pos().y(),mouse_click_x,mouse_click_y,condition,board[mouse_click_x][mouse_click_y],left_chess);
        //fflush(stdout);
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
                    ai_place(2);
                    //printf("x1:%d y1:%d x2:%d y2:%d",ai_x1,ai_y1,ai_x2,ai_y2);
                    //fflush(stdout);
                    board[ai_x1][ai_y1]=2;
                    board[ai_x2][ai_y2]=2;
                    left_chess=2;
                    condition=1;
                    repaint();
                    printf("P1");
                    fflush(stdout);


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
