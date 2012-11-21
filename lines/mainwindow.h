#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Qpainter>
#include <QImage>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int colRows;
    int colBalls;
    int colColors;
    int field[10][10];
    int numPoints;

    bool throw3balls(int iNum); //iNum - col of the balls to throw
    void setField(int x,int y, int BallColor);
    QImage* setImage(int index);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
