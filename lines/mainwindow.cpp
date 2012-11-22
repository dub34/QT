#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QVector>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->colRows=9;
    this->colColors=7;
    this->numPoints=0;//начальное кол-во очей
    this->colBalls=0;//начальное кол-во шаров

    for(int i=0;i<this->colRows;i++)
    {
        for (int j=0;j<this->colRows;j++)
        {
            this->field[i][j]=0; //заполнили начальное поле нолями
        }
    }
    this->throw3balls(5);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    QImage *image;

    QPainter painter(this);


    for(int i=0;i<9;i++)
    {
        for (int j=0;j<9;j++)
        {
            image=this->setImage(this->field[i][j]);
            painter.drawImage(i*24,j*24, image->scaledToWidth(24));

        }


    }
}

QImage* MainWindow::setImage(int index)
{
     QImage *image;

    switch (index)
    {
    case 1:
       image= new QImage(":/res/res/black.png");
    break;
   case 2:
        image=new QImage(":/res/res/BROWN.png");
    break;
    case 3:
         image=new QImage(":/res/res/BLUE.png");
     break;
    case 4:
         image=new QImage(":/res/res/GREEN.png");
     break;
    case 5:
         image=new QImage(":/res/res/RED.png");
     break;
    case 6:
         image=new QImage(":/res/res/ROSE.png");
     break;
    case 7:
         image=new QImage(":/res/res/YELLOW.png");
     break;
    default:
        image=new QImage(":/res/res/NO_COLOR.png");
    break;
    }

    return image;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    int i= event->x()/24;
    int j= event->y()/24;

    QString str;


qDebug() <<"i " << i << "j " << j;
qDebug() <<"field " << this->field[i][j];
if (this->field[i][j] !=0)
{
    Bmove=true;
    this->i0=i; //from x
    this->j0=j;//from y
    qDebug() <<"Select field: i" << i << "j " << j;
}
    else {
        qDebug() <<"move? " << this->Bmove;
        if (this->Bmove)
        {
            this->found=false;
            int CurState=this->field[i0][j0];
            this->field[this->i0][this->j0]=0;
            memset(this->path,0,sizeof(this->path));
            if (this->isPath(this->i0,this->j0,i,j)){

                this->field[this->i0][this->j0]=CurState;
                this->moveBall(this->i0,this->j0,i,j);

                this->Bmove=false;
                if (this->checkLines(i,j))
                {
                    if(this->colRows*this->colRows-this->colBalls>=3){
                         this->throw3balls(3);
                     }

                     else{

                         this->throw3balls(this->colRows*this->colRows-this->colBalls);
                     }

                     //Проверяем, есть не все ли клетки заняты

                     //Если да, то заканчиваем игру

                     if(this->colRows*this->colRows==this->colBalls){

                     }
                }
            }
            else{
                this->field[this->i0][this->j0]=CurState;
                qDebug() << "net puti";
            }
        }
        qDebug() << "shar ne vibran";
    }
    update();
}


bool MainWindow::throw3balls(int iNum){
    int i,j;
    int BallColor;

    if (iNum >0)
    {
        for(int k=0; k<iNum; k++)
        {
            do {
                i=rand()%this->colRows;
                j=rand()%this->colRows;
            }while(this->field[i][j]!=0);

            BallColor=rand()%this->colColors+1;
            this->setField(i,j,BallColor);
        }
        return true;
    }
    else {
        qDebug() << 'Net mesta. Game Over!';
        return false;
    }
}

void MainWindow::setField(int i, int j, int BallColor)
{
    this->field[i][j]=BallColor;
    qDebug() << "set field" << i << j << "value" << BallColor;
    if (BallColor !=0)
    {
        this->colBalls++;
    }else this->colBalls--;
    //this->SetModifiedFlag();
}

void MainWindow::moveBall(int iFrom, int jFrom, int iTo, int jTo){
    qDebug() <<"move ball from " << iFrom << jFrom << " to " << iTo << jTo;

    //int tmp = this->field[iTo][jTo];

    this->setField(iTo,jTo,this->field[iFrom][jFrom]);

    this->setField(iFrom,jFrom,0);
}

bool MainWindow::isPath(int iCur, int jCur, int iTo, int jTo){
    if (this->found) return this->found;

    if (iCur>=0 && iCur<this->colRows && jCur>=0 && jCur<this->colRows)
    {
        if(!this->path[iCur][jCur])
        {
            if(this->field[iCur][jCur] == 0)
            {
                this->path[iCur][jCur]++;
                qDebug() << "x=" << iCur << " y=" << jCur << endl;
                if (iCur==iTo && jCur==jTo)
                {
                    this->found=true;
                }
                else
                {
                    this->isPath(iCur-1,jCur,iTo,jTo);
                    this->isPath(iCur+1,jCur,iTo,jTo);
                    this->isPath(iCur,jCur-1,iTo,jTo);
                    this->isPath(iCur,jCur+1,iTo,jTo);
                }
            }
        }

    }
    return this->found;
}

bool MainWindow::checkLines(int i, int j)
{
    int color;
    int color_count_hor;
    bool search_done;
    int k,l;
    int i_cur,j_cur_l,j_cur_r;
    QVector<int> vector;

    //horizontal
    j_cur_r=j+1;
    j_cur_l=j-1;

    color=this->field[i][j];

    color_count_hor=1;

    search_done=false;

    while((j_cur_r<this->colRows || j_cur_l>=0) && !search_done)
    {
        if(this->field[i][j_cur_r]==color)
        {
            color_count_hor++;
            j_cur_r++;
        }
        if(this->field[i][j_cur_l]==color)
        {
            color_count_hor++;
            j_cur_l--;
        }
        if(this->field[i][j_cur_l]!=color && this->field[i][j_cur_r]!=color)
            search_done=true;


    }

    qDebug() << "color count hor" << color_count_hor <<endl;
    return true;
}
