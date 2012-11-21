#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
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

void MainWindow::paintEvent(QPaintEvent *)
{

    QImage image(":/images/BLACK.png");

    QPainter painter(this);
    int x(0),y(0);

    for(int i=0;i<=9;i++)
    {
        for (int j=0;j<=9;j++)
        {
            painter.drawImage(x,y, image.scaledToWidth(24));
            x=x+24;
        }
        x=0;
        y=y+24;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    qDebug() << "mouseClick at x:" << pos().x()
             << ' and pos y: ' << pos().y();
}
