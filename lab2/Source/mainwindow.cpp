#include "../Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this); // Создаём объект-живописец
    WorldToScreenConverter converter(0, 15, -100, 100, this->rect());
    AbscissaAxis abscissaAxis;
    abscissaAxis.draw(painter, converter);

    OrdinateAxis ordinateAxis;
    ordinateAxis.draw(painter, converter);
}