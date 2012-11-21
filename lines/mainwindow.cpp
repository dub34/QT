#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
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
    int x(0),y(0);

    for(int i=0;i<9;i++)
    {
        for (int j=0;j<9;j++)
        {
            image=this->setImage(this->field[i][j]);
            painter.drawImage(x,y, image->scaledToWidth(24));
            x=x+24;
        }
        x=0;
        y=y+24;
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
    if (event->button() == Qt::RightButton);
    {
    this->throw3balls(3);
    update();
    }
}

bool MainWindow::throw3balls(int iNum){
    int x,y;
    int BallColor;

    if (iNum >0)
    {
        for(int i=0; i<iNum; i++)
        {
            do {
                x=rand()%this->colRows;
                y=rand()%this->colRows;
            }while(this->field[x][y]!=0);

            BallColor=rand()%this->colColors+1;
            this->setField(x,y,BallColor);
        }
        return true;
    }
    else {
        qDebug() << 'Net mesta. Game Over!';
        return false;
    }
}

void MainWindow::setField(int x, int y, int BallColor)
{
    this->field[x][y]=BallColor;

    if (BallColor !=0)
    {
        this->colBalls++;
    }else this->colBalls--;
    //this->SetModifiedFlag();
}
