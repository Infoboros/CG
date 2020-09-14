#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>

#include "WorldToScreenConverter.h"
#include "Axis.h"
#include "Chart.h"
#include "CurveData.h"

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
    void on_aBox_valueChanged(double arg1);

    void on_bBox_valueChanged(double arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *p) override;
};

#endif // MAINWINDOW_H
