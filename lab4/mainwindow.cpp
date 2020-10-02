
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p) {
    QWidget::paintEvent(p);
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(Qt::black, 5));

    Object tumbOchka = Tumba();
    Matr rt_x = RotateMX(90*RAD);
    Matr rt_y = RotateMY(0);
    Matr rt_z = RotateMZ(0);

    int center_x = width() / 2;
    int center_y = height() / 2;

    // Вычисляем радиус внешней окружности
    double radius = ((width() / 2. > height() ? height() : width() / 2.) - 20) / 2;

    painter.translate(center_x, center_y);

    Object vertate = (rt_z*rt_x*rt_y)*tumbOchka;

    vertate.draw(painter);

}

void MainWindow::wheelEvent(QWheelEvent *wheelevent) {
    angle += wheelevent->delta() / 100000.;
    repaint();
}

