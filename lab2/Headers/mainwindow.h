#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>

#include "../Headers/WorldToScreenConverter.h"
#include "../Headers/Axis.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    // Обработчик события перерисовки окна
    void paintEvent(QPaintEvent* event) override;

};

#endif // MAINWINDOW_H
