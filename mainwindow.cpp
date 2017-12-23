#include "mainwindow.h"
#include "ui_mainwindow.h"
#define max_x 11
#define max_y 11
#define windowsize_x 1200
#define windowsize_y 750
int zoom = 45;

int alpha_count=0;
int beta_count=0;
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
int board[max_x+1][max_y+1];
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
                board[7][7]=1;

                board[2][10]=1;*/


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
        count_value(value);*/
    /*
        int v_max_x=0,v_min_x=0, v_max_y=0, v_min_y=0;
        chess_center(&v_max_x,&v_min_x,&v_max_y,&v_min_y);
        printf("max_x:%d min_x:%d max_y:%d min_y:%d\n",v_max_x,v_min_x,v_max_y,v_min_y);
        fflush(stdout);*/
}


MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::chess_center(int x,int y)
{
    int i,j;
    int temp_x;
    int temp_y;
    for(i=-2; i<=2; i++)
    {
        for(j=-2; j<=2; j++)
        {
            temp_x=x+i;
            temp_y=y+j;
            if(temp_x>=1&&temp_x<=max_x&&temp_y<=max_y&&temp_y>=1&&board[temp_x][temp_y]!=0)
            {
                return 1;
            }
        }
    }
    return 0;
}
int MainWindow::judge_value(int t, int flag, int space)
{
    int table[7][3]= {0,0,0
                      ,10,5,1
                      ,50,20,2
                      ,100,70,10
                      ,1000,150,40
                      ,3000,1500,80
                      ,100000,100000,100000
                     };
    if(t>=6)
    {
        return 100000;
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
int MainWindow::ai_place(int player, int layer, int *alpha, int *beta,int is_first_node, int max_layer)
{
    int local_minscore=0;
    int local_maxscore=0;
    int local_minscore_first_flag=1;
    int local_maxscore_first_flag=1;
    if(layer==max_layer)
    {
        int value[3]= {0};
        count_value(value);
        return value[2]-value[1];
    }

    int i,j,k,l;
    int local_is_first_node=is_first_node;
    int local_alpha_first_flag=1;
    int local_beta_first_flag=1;

    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            if(!chess_center(i,j))
            {
                continue;
            }
            if(board[i][j]==0)
            {
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

                                if(!chess_center(k,l))
                                {
                                    continue;
                                }
                                board[i][j]=player;
                                board[k][l]=player;

                                int temp=0;/*
                                if(layer%2==1&&layer<=max_layer-2)
                                {
                                    local_beta_first_flag=0;
                                    *beta=0;
                                    //printf("@@beta\n");
                                    //fflush(stdout);
                                }*/
                                if(layer%2==0&&layer<=max_layer-2&&local_alpha_first_flag==1)
                                {
                                    local_alpha_first_flag=0;
                                    *alpha=0;/*
                                    printf("@@alpha\n");
                                    fflush(stdout);*/
                                }
                                if(layer<max_layer)
                                {
                                    if(player==1)
                                    {
                                        temp=ai_place(2,layer+1,alpha,beta,is_first_node,max_layer);
                                    }
                                    else
                                    {
                                        temp=ai_place(1,layer+1,alpha,beta,is_first_node,max_layer);
                                    }
                                    if(temp==-1)
                                    {
                                        board[i][j]=0;
                                        board[k][l]=0;
                                        continue;
                                    }
                                    is_first_node=0;
                                }

                                if (local_is_first_node==1&&layer%2==1)
                                {
                                    if(*alpha>temp||*alpha==0)
                                    {
                                        *alpha=temp;
                                    }
                                }/*
                                else if(local_is_first_node==1&&layer%2==0)
                                {
                                    if(*beta<temp||*beta==0)
                                    {
                                        *beta=temp;
                                    }
                                    //printf("beta:%d temp:%d\n",*beta,temp);
                                    //fflush(stdout);
                                }*/


                                else if(local_is_first_node==0&&layer%2==1)
                                {
                                    //alpha cut
                                    if(*alpha>temp&&*alpha!=0)
                                    {
                                        alpha_count++;
                                        board[i][j]=0;
                                        board[k][l]=0;
                                        return -1;
                                    }
                                }
                                else if(local_is_first_node==0&&layer%2==0)
                                {
                                    //beta cut
                                    if(*beta<temp&&*beta!=0)
                                    {

                                        beta_count++;
                                        board[i][j]=0;
                                        board[k][l]=0;
                                        return -1;
                                    }
                                }

                                if(layer==1)
                                {
                                    //printf("x1:%d y1:%d x2:%d y2:%d temp:%d\n",i,j,k,l,temp);
                                    //fflush(stdout);
                                }
                                if(temp>local_maxscore||local_maxscore_first_flag)
                                {
                                    local_maxscore_first_flag=0;
                                    local_maxscore=temp;
                                    if(layer==0)
                                    {
                                        //printf("@@max:%d temp:%d\n",local_maxscore, temp);
                                        //fflush(stdout);
                                        ai_x1=i;
                                        ai_y1=j;
                                        ai_x2=k;
                                        ai_y2=l;
                                    }
                                }
                                if(temp<local_minscore||local_minscore_first_flag)
                                {
                                    local_minscore_first_flag=0;
                                    local_minscore=temp;
                                }
                                board[i][j]=0;
                                board[k][l]=0;
                            }
                        }
                    }
                }
            }
            if(layer==0)
            {
                int t=time.elapsed();
                printf("t:%6.2f alpha:%d beta:%d ",t/1000.0,alpha_count,beta_count);
                printf("max: x1:%d y1:%d x2:%d y2:%d ",ai_x1,ai_y1,ai_x2,ai_y2);
                printf("local x:%d y:%d\n",i,j);
                fflush(stdout);
            }
        }
    }

    if(layer%2==0&&local_is_first_node==0)
    {
        if(*beta>local_maxscore&&*beta!=0)
        {
            *beta=local_maxscore;
        }
    }



    if(layer%2==0)
    {
        return local_maxscore;
    }
    else
    {
        return local_minscore;
    }
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
    painter.setPen(QPen(Qt::magenta, zoom*3/5));
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
                time.start();
                int alpha=0,beta=0;
                alpha_count=0;
                beta_count=0;
                ai_place(2,0,&alpha,&beta,1,2);

                printf("x1:%d y1:%d x2:%d y2:%d\n",ai_x1,ai_y1,ai_x2,ai_y2);
                fflush(stdout);
                board[ai_x1][ai_y1]=2;
                board[ai_x2][ai_y2]=2;

                repaint();

                total_chess+=2;
                left_chess=2;
                condition=1;
                printf("P1\n");
                fflush(stdout);
            }/*
            int i,j;
            for(i=1;i<=max_x;i++)
            {
                for(j=1;j<=max_y;j++)
                {
                    printf("%d ",board[i][j]);
                }
                printf("\n");
            }
            int v_max_x=0,v_min_x=0, v_max_y=0, v_min_y=0;
            chess_center(&v_max_x,&v_min_x,&v_max_y,&v_min_y);
            printf("max_x:%d min_x:%d max_y:%d min_y:%d\n",v_max_x,v_min_x,v_max_y,v_min_y);

            fflush(stdout);*/
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
