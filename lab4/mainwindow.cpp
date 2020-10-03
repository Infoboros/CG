
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        dilatation(DilatationM(1, 1, 1)),
        rotate(RotateMY(0)){
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

    // Радиус большей окружности
    float radius;
    // Вычисляем радиус окружности
    if (width() > height()) // Если ширина окна больше высоты
        radius = (height() - 20) / 2; // Отступ от краёв - 10 пикселей
    else radius = (width() - 20) / 2;

    Object staticTumba = Tumba(radius/290.);

    // Координаты центра всего
    QPointF center = QPointF(width() / 2, height() / 2);

    painter.translate(center.x(), center.y());

    painter.translate(-radius/2., -radius/2.);
    staticTumba.drawFront(painter);

    painter.translate(radius, 0);
    staticTumba.drawPorf(painter);

    painter.translate(-radius, radius);
    staticTumba.drawUp(painter);

    painter.translate(radius, 0);
    drawDinamic(painter, radius);

    painter.translate(-radius/2., -radius/2.);
    painter.setPen(Qt::blue);
    drawAxis(painter, radius);

}

void MainWindow::wheelEvent(QWheelEvent *wheelevent) {
    double k = 1. + wheelevent->delta() / 10000.;
    Matr dilatationMnog = DilatationM(k, k, k);
    dilatation = dilatationMnog*dilatation;
    repaint();
}

void MainWindow::drawAxis(QPainter &painter, double radius) {
    painter.drawLine(-radius/2., -radius, -radius/2., radius);
    painter.drawLine(-radius, -radius/2., radius, -radius/2.);
}

void MainWindow::drawDinamic(QPainter &painter, double radius) {
    Object tumba = Tumba(radius/290.);
    tumba = dilatation*tumba;
    tumba = rotate*tumba;

    tumba.draw(painter);
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (!oldXpos)
        oldXpos = cursor().pos().x();
    else{
        double newXPos = cursor().pos().x();
        double k = 1. + (newXPos - oldXpos) / 10000.;

        int mnog = 1;
        if (newXPos < oldXpos)
            mnog = -1;
        oldXpos = newXPos;

        Matr rotateMnog = RotateMY(mnog*k*RAD);
        rotate = rotateMnog*rotate;
        repaint();
    }
}

