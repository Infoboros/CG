
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        dilatation(500),
        rotate(){
    ui->setupUi(this);
    rotate.rotate(0, 0, 1, 0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p) {
    QWidget::paintEvent(p);
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(Qt::black, 5));

    // Радиус большей окружности
    float radius;
    // Вычисляем радиус окружности
    if (width() > height()) // Если ширина окна больше высоты
        radius = (height() - 20) / 2; // Отступ от краёв - 10 пикселей
    else radius = (width() - 20) / 2;

    // Координаты центра всего
    QPointF center = QPointF(width() / 2, height() / 2);

    painter.translate(center.x(), center.y());
    drawDinamic(painter, radius);


}

void MainWindow::wheelEvent(QWheelEvent *wheelevent) {
    dilatation += wheelevent->delta() / 10.;
    repaint();
}

void MainWindow::drawAxis(QPainter &painter, double radius) {
    painter.drawLine(-radius / 2., -radius, -radius / 2., radius);
    painter.drawLine(-radius, -radius / 2., radius, -radius / 2.);
}

void MainWindow::drawDinamic(QPainter &painter, double radius) {
    Object tumba = Tumba(radius / 290., 50);
    tumba = rotate * tumba;
    QMatrix4x4 proect(1., 0, 0, 0,
                      0, 1., 0, 0,
                      0, 0, 0, 0,
                      0, 0, 1 / dilatation, 1.);
    tumba.draw(painter, proect);
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (!oldXpos || !oldYpos) {
        oldXpos = cursor().pos().x();
        oldYpos = cursor().pos().y();
    } else {
        double newXPos = cursor().pos().x();
        double ky = 1. + (newXPos - oldXpos) / 10000.;

        double newYPos = cursor().pos().y();
        double kx = 1. + (newYPos - oldYpos) / 10000.;

        int mnogY = -1;
        if (newXPos < oldXpos)
            mnogY = 1;
        oldXpos = newXPos;

        int mnogX = 1;
        if (newYPos > oldYpos)
            mnogX = -1;
        oldYpos = newYPos;
        QMatrix4x4 rotateMnogY, rotateMnogX;
        rotateMnogY.rotate(mnogY * ky * RAD, 0, 1, 0);
        rotateMnogX.rotate(mnogX * kx * RAD, 1, 0, 0);

        rotate = rotateMnogY * rotate;
//        rotate = rotateMnogX * rotate;
        repaint();
    }
}
