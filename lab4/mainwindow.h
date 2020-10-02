#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>

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

private:
    double angle;
    double dilation;
    bool dilation_flag;
    int check_delete;
    vector<vector<QPointF>> mini_figures;
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *p) override;
    // Обработчик события прокрутки колеса мыши
    void wheelEvent(QWheelEvent* );

    void drawCircle(QPainter &painter, double radius);
    void drawStar(QPainter &painter, double big_radius, double small_radius, Matr &pr_matr);
    void drawMini(QPainter &painter, int radius, Matr pr_m);
};

#endif // MAINWINDOW_H
