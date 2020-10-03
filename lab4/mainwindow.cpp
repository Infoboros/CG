
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        dilatation(DilatationM(1, 1, 1)),
        rotate(RotateMY(0)),
        flag(0),
        sizeCenter(15){
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
    Matr dilatationMnog = DilatationM(k, k, k);
    dilatation = dilatationMnog * dilatation;
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

    Matr proect = RotateMY(45 * RAD);
    if (flag == 1) {
        //косоугольная кабинетная
        Matr rt_x = RotateMX(45 * RAD);
        proect = (rt_x * proect);
    } else if (flag == 2) {
        //косоугольная свободная
        Matr rt_x = RotateMX(30 * RAD);
        proect = (rt_x * proect);
    } else if (flag == 3) {
        //прямоугольная диметрия
        Matr rt_x = RotateMX((7 + 1. / 6.) * RAD);
        Matr rt_y = RotateMY((41 + 25./60.) * RAD);
        proect = (rt_x * rt_y * proect);
    } else if (flag == 4) {
        //прямоугольная изометрия
        Matr rt_x = RotateMX(30 * RAD);
        Matr rt_y = RotateMY(30 * RAD);
        proect = (rt_x * rt_y * proect);
    }


    tumba = proect * tumba;
    tumba.draw(painter);
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (!oldXpos || !oldYpos) {
        oldXpos = cursor().pos().x();
        oldYpos = cursor().pos().y();
    }else {
        double newXPos = cursor().pos().x();
        double ky = 1. + (newXPos - oldXpos) / 10000.;

//        double newYPos = cursor().pos().y();
//        double kx = 1. + (newYPos - oldYpos) / 10000.;

        int mnogY = 1;
        if (newXPos < oldXpos)
            mnogY = -1;
        oldXpos = newXPos;

//        int mnogX = 1;
//        if (newYPos > oldYpos)
//            mnogX = -1;
//        oldYpos = newYPos;

        Matr rotateMnogY = RotateMY(mnogY * ky * RAD);
//        Matr rotateMnogX = RotateMZ(mnogX * kx * RAD);

        rotate = rotateMnogY * rotate;
//        rotate = rotateMnogX * rotate;
        repaint();
    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index) {
    flag = index;
    repaint();
}

void MainWindow::on_textEdit_selectionChanged()
{
    sizeCenter = ui->textEdit->toPlainText().toInt();
}
