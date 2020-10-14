#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>
#include <QMatrix4x4>

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

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_textEdit_selectionChanged();

private:
    double oldXpos;
    double oldYpos;
    int flag;
    double sizeCenter;

    QMatrix4x4 dilatation;
    QMatrix4x4 rotate;

    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *p) override;
    // Обработчик события прокрутки колеса мыши
    void wheelEvent(QWheelEvent* ) override;
    void mouseMoveEvent(QMouseEvent* );

    void drawAxis(QPainter &painter, double radius);
    void drawDinamic(QPainter &painter, double radius);
};

#endif // MAINWINDOW_H
