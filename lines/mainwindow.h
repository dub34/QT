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
    int path[10][10];
    bool found;
    int numPoints;

    bool Bmove;
    int i0;
    int j0;

    bool throw3balls(int iNum); //iNum - col of the balls to throw
    void setField(int i,int j, int BallColor);
    void moveBall(int iFrom,int jFrom, int iTo, int jTo);
    bool isPath(int iCur, int jCur, int iTo, int jTo);
    bool checkLines(int i, int j);
    QImage* setImage(int index);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
