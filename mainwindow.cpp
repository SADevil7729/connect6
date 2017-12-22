#include "mainwindow.h"
#include "ui_mainwindow.h"
#define max_x 11
#define max_y 11
#define windowsize_x 1200
#define windowsize_y 800
int zoom = 45;

int time_count=1;
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
int total_chess=0;
int condition=1;
int left_chess=1;
QTime time;
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

    /*
            board[3][3]=2;
            board[3][4]=2;
            board[4][5]=2;
            board[4][4]=1;
            board[5][5]=1;
            board[6][6]=1;

            board[5][6]=1;

            board[5][7]=1;
            board[6][7]=1;
            board[7][7]=1;*/


    /*
            board[9][11]=1;
            board[10][11]=1;

            board[11][11]=1;
            board[10][10]=1;*/
    /*
            int x=0,y=0;
            chess_center(&x,&y);
            printf("x%d y%d",x,y);*/

    /*
        int value[3]={0};
        count_value(value);
        printf("p1:%d , p2:%d\n",value[1],value[2]);
        fflush(stdout);*/
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::chess_center(int *value_x,int *value_y)
{
    int i,j;
    int count=0;
    *value_x=0;
    *value_y=0;
    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            if(board[i][j]!=0)
            {
                count++;
                *value_x+=i;
                *value_y+=j;
            }
        }
    }
    *value_x/=count;
    *value_y/=count;
    return ;
}
int MainWindow::judge_value(int t, int flag, int space)
{
    int table[7][3]= {0,0,0
                      ,10,5,1
                      ,50,20,2
                      ,100,70,10
                      ,1000,150,40
                      ,3000,1500,80
                      ,1000000,1000000,1000000
                     };
    if(t>=6)
    {
        return 1000000;
    }
    float space_coeff=1.0;/*
    if(space>=4)
    {
        space_coeff=3.0;
    }
    else
    {
        space_coeff=(1.0+space*0.5);
    }*/

    int value=table[t][flag]*space_coeff;
    /*
    if(value!=0)
    {
    printf("value%d connect:%d flag:%d\n",value,t,flag);
    fflush(stdout);
    }*/
    return value;
}
void MainWindow::judge7(int value[])//   '\'
{
    int mem_x=1,mem_y=max_y;
    int i=1,j=max_y;
    int connect=0;
    int now_player=0;
    int flag=1;
    int space=0;
    int break_flag=0;

    while(1)
    {
        if(break_flag==1)
        {
            break;
        }
        if(now_player==0&&board[i][j]==0)
        {
            space++;
            flag=0;
            connect=0;
        }
        else if(now_player!=0&&board[i][j]==now_player)
        {
            //如果連續
            connect++;
        }
        else if(now_player!=0&&now_player!=board[i][j])
        {
            //下一格不等於本身
            if(board[i][j]!=0)
            {
                //如果遇到對手的棋

                flag++;
                value[now_player]+=judge_value(connect,flag,space);
                now_player=board[i][j];
                connect=1;
                flag=1;//對手的flag會是1
            }
            else
            {
                //空白
                value[now_player]+=judge_value(connect,flag,space);
                flag=0;
                connect=0;
                now_player=0;
                space=1;
            }
        }
        else if(now_player==0&&board[i][j]!=0)
        {
            //開新的棋串
            now_player=board[i][j];
            connect=1;
        }

        //printf("p1:%d , p2:%d\n",value[1],value[2]);
        fflush(stdout);
        i++;
        j++;


        if(mem_x==max_x&&mem_y==1)
        {
            break_flag=1;
        }

        if(i>max_x||j>max_y)
        {
            value[now_player]+=judge_value(connect,flag+1,space);
            flag=1;
            now_player=0;
            connect=0;
            if(mem_y>1)
            {
                mem_y--;
                i=mem_x;
                j=mem_y;
            }
            else if(mem_x<max_x)
            {
                mem_x++;
                i=mem_x;
                j=mem_y;
            }
        }
    }
}
void MainWindow::judge4(int value[])//   '—'
{

    int mem_x=1,mem_y=1;
    int i=1,j=1;
    int connect=0;
    int now_player=0;
    int flag=1;
    int space=0;
    int break_flag=0;

    while(1)
    {
        if(break_flag==1)
        {
            break;
        }
        if(now_player==0&&board[i][j]==0)
        {
            flag=0;
            connect=0;
            space++;
        }
        else if(now_player!=0&&board[i][j]==now_player)
        {
            //如果連續
            connect++;
        }
        else if(now_player!=0&&now_player!=board[i][j])
        {
            //下一格不等於本身
            if(board[i][j]!=0)
            {
                //如果遇到對手的棋

                flag++;
                value[now_player]+=judge_value(connect,flag,space);
                now_player=board[i][j];
                connect=1;
                flag=1;//對手的flag會是1
            }
            else
            {
                //空白
                value[now_player]+=judge_value(connect,flag,space);
                flag=0;
                connect=0;
                now_player=0;
                space=1;
            }
        }
        else if(now_player==0&&board[i][j]!=0)
        {
            //開新的棋串
            now_player=board[i][j];
            connect=1;
            flag=0;
            space=1;
        }


        //printf("i:%d j:%d\n",i,j);
        //printf("p1:%d , p2:%d\n",value[1],value[2]);
        fflush(stdout);

        if(i==max_x&&j==max_y)
        {
            break_flag=1;
        }

        if(i<max_x)
        {
            i++;
        }
        else
        {
            value[now_player]+=judge_value(connect,flag+1,space);
            flag=1;
            mem_y++;
            i=mem_x;
            j=mem_y;
        }
    }
}
void MainWindow::judge8(int value[])//   |
{

    int mem_x=1,mem_y=1;
    int i=1,j=1;
    int connect=0;
    int now_player=0;
    int flag=1;
    int space=0;

    int break_flag=0;

    while(1)
    {
        if(break_flag==1)
        {
            break;
        }
        if(now_player==0&&board[i][j]==0)
        {
            space++;
            flag=0;
            connect=0;
        }
        else if(now_player!=0&&board[i][j]==now_player)
        {
            //如果連續
            connect++;
        }
        else if(now_player!=0&&now_player!=board[i][j])
        {
            //下一格不等於本身
            if(board[i][j]!=0)
            {
                //如果遇到對手的棋

                flag++;
                value[now_player]+=judge_value(connect,flag,space);
                now_player=board[i][j];
                connect=1;
                flag=1;//對手的flag會是1
            }
            else
            {
                //空白
                value[now_player]+=judge_value(connect,flag,space);
                flag=0;
                connect=0;
                now_player=0;
                space=1;
            }
        }
        else if(now_player==0&&board[i][j]!=0)
        {
            //開新的棋串
            now_player=board[i][j];
            connect=1;
        }

        //printf("i:%d j:%d\n",i,j);
        //printf("p1:%d , p2:%d\n",value[1],value[2]);
        fflush(stdout);

        if(i==max_x&&j==max_y)
        {
            break_flag=1;
        }

        if(j<max_y)
        {
            j++;
        }
        else
        {
            value[now_player]+=judge_value(connect,flag+1,space);
            flag=1;
            now_player=0;
            connect=0;
            mem_x++;
            i=mem_x;
            j=mem_y;
        }
    }
}
void MainWindow::judge9(int value[])//   '/'
{
    int mem_x=max_x,mem_y=max_y;
    int i=max_x,j=max_y;
    int connect=0;
    int now_player=0;
    int flag=1;

    int space=0;

    int break_flag=0;

    while(1)
    {
        if(break_flag==1)
        {
            break;
        }
        if(now_player==0&&board[i][j]==0)
        {
            space++;
        }
        else if(now_player!=0&&board[i][j]==now_player)
        {
            //如果連續
            connect++;
        }
        else if(now_player!=0&&now_player!=board[i][j])
        {
            //下一格不等於本身
            if(board[i][j]!=0)
            {
                //如果遇到對手的棋

                flag++;
                value[now_player]+=judge_value(connect,flag,space);
                now_player=board[i][j];
                connect=1;
                flag=1;//對手的flag會是1
            }
            else
            {
                //空白
                value[now_player]+=judge_value(connect,flag,space);
                flag=0;
                connect=0;
                now_player=0;
                space=1;
            }
        }
        else if(now_player==0&&board[i][j]!=0)
        {
            //開新的棋串
            now_player=board[i][j];
            connect=1;
        }

        //printf("i:%d j:%d\n",i,j);
        //printf("p1:%d , p2:%d\n",value[1],value[2]);
        fflush(stdout);
        i++;
        j--;


        if(mem_x==1&&mem_y==1)
        {
            break_flag=1;
        }


        if(i>max_x||j<1)
        {
            value[now_player]+=judge_value(connect,flag+1,space);
            flag=1;
            now_player=0;
            connect=0;
            if(mem_x>1)
            {
                mem_x--;
                i=mem_x;
                j=mem_y;
            }
            else if(mem_y>1)
            {
                mem_y--;
                i=mem_x;
                j=mem_y;
            }
        }
    }
}
void MainWindow::count_value(int *value)
{
    //printf("4\n");
    //fflush(stdout);
    judge4(value);

    //printf("7\n");
    //fflush(stdout);
    judge7(value);

    //printf("8\n");
    //fflush(stdout);
    judge8(value);

    //printf("9\n");
    //fflush(stdout);
    judge9(value);
}
int MainWindow::ai_place(int player,int layer,int max_value[])
{
    int i,j,k,l;
    int local_score=0;
    int temp=0;
    if(layer==2)
    {
        int value[3]= {0};
        count_value(value);
        local_score=value[2]-value[1];
        /*
        if(layer%2==1&&(value[2]-value[1]>local_score||local_score==0))
        {
            local_score=value[2]-value[1];
        }
        if(layer%2==0&&(value[2]-value[1]<local_score||local_score==0))
        {
            local_score=value[2]-value[1];
        }*/
        return local_score;
    }


    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            if(board[i][j]==0)
            {
                /*
                int x=0,y=0;
                chess_center(&x,&y);
                if(abs(i-x)>=2+total_chess/2||abs(j-y)>=2+total_chess/2)
                {
                    continue;
                }*/

                for(k=i; k<=max_x; k++)
                {
                    if(k!=i)
                    {
                        l=1;
                    }
                    else
                    {
                        l=j+1;
                    }
                    for(; l<=max_y; l++)
                    {
                        if(board[k][l]==0)//empty
                        {
                            if(i==k&&j==l)
                            {
                                continue;
                            }
                            else
                            {
                                /*
                                       int x2=0,y2=0;
                                       chess_center(&x2,&y2);
                                       if(abs(k-x2)>=2+total_chess/2||abs(l-y2)>=2+total_chess/2)
                                       {
                                           continue;
                                       }*/

                                board[i][j]=player;
                                board[k][l]=player;


                                if(layer<2)
                                {
                                    if(player==1)
                                    {
                                        temp=ai_place(2,layer+1,max_value);
                                    }
                                    else
                                    {
                                        temp=ai_place(1,layer+1,max_value);
                                    }
                                    if (layer%2==1&&(temp<local_score||local_score==0))
                                    {
                                        local_score=temp;
                                        if(layer==1)
                                        {
                                            ai_x1=i;
                                            ai_y1=j;
                                            ai_x2=k;
                                            ai_y2=l;
                                            printf("score%d max: x1:%d y1:%d x2:%d y2:%d ",local_score,ai_x1,ai_y1,ai_x2,ai_y2);
                                            //printf("local x1:%d y1:%d x2:%d y2:%d\n",i,j,k,l);
                                            fflush(stdout);

                                        }
                                    }
                                    else if(layer%2==0&&(temp<local_score||local_score==0))
                                    {
                                        local_score=temp;
                                    }
                                }
                                /*
                                if(layer==1)
                                {
                                    //int t=0;
                                    //t=time.elapsed();
                                    //time_count++;
                                    //printf("t:%d speed:%f ",,t,time_count*1000.0/t);
                                    printf("score%d max: x1:%d y1:%d x2:%d y2:%d ",local_score,ai_x1,ai_y1,ai_x2,ai_y2,i,j,k,l);
                                    printf("local x1:%d y1:%d x2:%d y2:%d\n",i,j,k,l);
                                    fflush(stdout);
                                }*/
                                board[i][j]=0;
                                board[k][l]=0;
                            }
                        }
                    }
                }
                /*
                                if(max_value[1]<local_score)
                                {
                                    max_value[1]=local_score;
                                }*/
            }
        }
    }

    return local_score;
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


    for (i = 1; i <= max_x+1; i++)
    {
        painter.drawLine(i * zoom, zoom, i * zoom, max_y * zoom+zoom);
    }
    for (j = 1; j <= max_y+1; j++)
    {
        painter.drawLine(zoom, j * zoom, max_x * zoom+zoom, j * zoom);
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
        if (zoom < 45)
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
        if(board[mouse_click_x][mouse_click_y]==0&&mouse_click_x>=1&&mouse_click_x<=max_x&&mouse_click_y>=1&&mouse_click_y<=max_y)
        {
            board[mouse_click_x][mouse_click_y]=1;
            repaint();
            left_chess--;
            total_chess++;
            if(left_chess<=0)
            {
                condition=2;
                int max_value[3]= {0};
                time.start();
                ai_place(2,1,max_value);

                printf("x1:%d y1:%d x2:%d y2:%d",ai_x1,ai_y1,ai_x2,ai_y2);
                fflush(stdout);
                board[ai_x1][ai_y1]=2;
                board[ai_x2][ai_y2]=2;

                repaint();

                total_chess+=2;
                left_chess=2;
                condition=1;
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
