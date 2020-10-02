#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>

#include "Headers/model3d.h"

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

    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *p) override;
    // Обработчик события прокрутки колеса мыши
    void wheelEvent(QWheelEvent* );
};

#endif // MAINWINDOW_H
