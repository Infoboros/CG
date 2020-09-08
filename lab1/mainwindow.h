#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int angle;

    // Обработчик события перерисовки окна
    void paintEvent(QPaintEvent* event);

    // Обработчик события прокрутки колеса мыши
    void wheelEvent(QWheelEvent* );

    //Больщой квадрат
    void drawBigRect(QPainter &painter, float aBigRect);
    //Маленькие окружности
    void drawSmallCircle(QPainter &painter, float bigRectRadius);
    //Маленьких ромбика
    void drawSmalRomb(QPainter &painter, float widthR, float heightR, float bigRectRadius, float radius);
    //Маленький круг
    void drawSmallCenterCircle(QPainter &painter);
};

#endif // MAINWINDOW_H
