
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        dilatation(),
        rotate(),
        flag(0),
        sizeCenter(15) {
    ui->setupUi(this);
    dilatation.scale(0.94);
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

    Object staticTumba = Tumba(radius / 290., sizeCenter);

    // Координаты центра всего
    QPointF center = QPointF(width() / 2, height() / 2);

    painter.translate(center.x(), center.y());

    painter.translate(-radius / 2., -radius / 2.);
    staticTumba.drawFront(painter);

    painter.translate(radius, 0);
    staticTumba.drawPorf(painter);

    painter.translate(-radius, radius);
    staticTumba.drawUp(painter);

    painter.translate(radius, 0);
    drawDinamic(painter, radius);

    painter.translate(-radius / 2., -radius / 2.);
    painter.setPen(Qt::blue);
    drawAxis(painter, radius);

}

void MainWindow::wheelEvent(QWheelEvent *wheelevent) {
    double k = 1. + wheelevent->delta() / 10000.;
    dilatation.scale(k);
    repaint();
}

void MainWindow::drawAxis(QPainter &painter, double radius) {
    painter.drawLine(-radius / 2., -radius, -radius / 2., radius);
    painter.drawLine(-radius, -radius / 2., radius, -radius / 2.);
}

void MainWindow::drawDinamic(QPainter &painter, double radius) {
    Object tumba = Tumba(radius / 290., sizeCenter);
    tumba = dilatation * tumba;
    tumba = rotate * tumba;

    QMatrix4x4 proect, rt_x, rt_y;

    if (flag == 0) {
        //центральная
        proect = QMatrix4x4(1., 0, 0, 0,
                            0, 1., 0, 0,
                            0, 0, 0, 0,
                            0, 0, 1 / 400., 1.);
    } else if (flag == 1) {
        //косоугольная кабинетная
        double a_b = -cos(3.14 / 4.) / 2.;
        proect = QMatrix4x4(1., 0, a_b, 0,
                            0, 1., a_b, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 1.);
    } else if (flag == 2) {
        //косоугольная свободная
        double a_b = -cos(3.14 / 4.);
        proect = QMatrix4x4(1., 0, a_b, 0,
                            0, 1., a_b, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 1.);
        proect.scale(0.7);
    } else if (flag == 3) {
        //Ортографическая
        proect = QMatrix4x4(1., 0, 0, 0,
                            0, 1., 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 1.);
    } else if (flag == 4) {
        //прямоугольная диметрия
        rt_x.rotate((7 + 1. / 6.) * RAD, 1, 0, 0);
        rt_y.rotate((41 + 25. / 60.) * RAD, 0, 1, 0);
        proect = (rt_x * rt_y * proect);
    } else if (flag == 5) {
        //прямоугольная изометрия
        rt_x.rotate(30 * RAD, 1, 0, 0);
        rt_y.rotate(30 * RAD, 0, 1, 0);
        proect = (rt_x * rt_y * proect);
    }

    tumba = proect * tumba;
    tumba.draw(painter);
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


void MainWindow::on_comboBox_currentIndexChanged(int index) {
    flag = index;
    repaint();
}

void MainWindow::on_pushButton_clicked()
{
    sizeCenter = ui->textEdit->toPlainText().toDouble();
    if (sizeCenter > 120.)
        sizeCenter = 120;
    if (sizeCenter <1)
        sizeCenter = 1;
    repaint();
}
