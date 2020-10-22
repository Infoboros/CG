#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>
#include <QEventLoop>

#include "Headers/afin_matr.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    double angle;
    int check_delete;
    bool start;
    vector<vector<QPointF>> mini_figures;
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *p) override;

    void drawAxis(QPainter &painter, double radius, Matr r_m);
    void drawFan(QPainter &painter, double radius, Matr r_m);
    void drawMini(QPainter &painter, int radius, Matr pr_m);
};

#endif // MAINWINDOW_H
