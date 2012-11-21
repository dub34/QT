#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPicture>
#include <QImage>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    int colRows;
    int colColors;
    int colBalls;
    int field[9][9];

    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
