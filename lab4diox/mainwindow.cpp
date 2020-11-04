
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        dilatation(DilatationM(1, 1, 1)),
        rotate(RotateMY(0)),
        flag(0),
        sizeCenter(5){
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p) {
    QWidget::paintEvent(p);
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(QPen(Qt::black, 1));

    // Радиус большей окружности
    float radius;
    // Вычисляем радиус окружности
    if (width() > height()) // Если ширина окна больше высоты
        radius = (height() - 20) / 2; // Отступ от краёв - 10 пикселей
    else radius = (width() - 20) / 2;

    Object staticLampa = Lampa(sizeCenter);

    // Координаты центра всего
    QPointF center = QPointF(width() / 2, height() / 2);

    painter.translate(center.x(), center.y());

    painter.translate(-radius / 2., -radius / 2.);
    staticLampa.drawFront(painter);

    painter.translate(radius, 0);
    staticLampa.drawPorf(painter);

    painter.translate(-radius, radius);
    staticLampa.drawUp(painter);

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
    Object lamp = Lampa(sizeCenter);
    lamp = dilatation * lamp;
    lamp = rotate * lamp;

    //по умолчанию центральная
    Matr proect = Matr({{1., 0, 0, 0},
                        {0, 1., 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 1. / 10., 1.}});
    if (flag == 1) {
        //косоугольная кабинетная
        double a_b = -cos(3.14 / 4.) / 2.;
        proect = Matr({{1., 0, a_b, 0},
                       {0, 1., a_b, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 1.}});
    } else if (flag == 2) {
        //косоугольная свободная
        double a_b = -cos(3.14 / 4.);
        proect = Matr({{1., 0, a_b, 0},
                       {0, 1., a_b, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 1.}});
    } else if (flag == 3) {
        //прямоугольная диметрия
        proect = RotateMY(45 * RAD);
        Matr rt_x = RotateMX((7 + 1. / 6.) * RAD);
        Matr rt_y = RotateMY((41 + 25./60.) * RAD);
        proect = (rt_x * rt_y * proect);
    } else if (flag == 4) {
        //прямоугольная изометрия
        proect = RotateMY(45 * RAD);
        Matr rt_x = RotateMX(30 * RAD);
        Matr rt_y = RotateMY(30 * RAD);
        proect = (rt_x * rt_y * proect);
    }

    lamp = proect * lamp;
    lamp.draw(painter);
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (!oldXpos || !oldYpos) {
        oldXpos = cursor().pos().x();
        oldYpos = cursor().pos().y();
    }else {
        double newXPos = cursor().pos().x();
        double ky = 1. + (newXPos - oldXpos) / 10000.;

        int mnogY = 1;
        if (newXPos < oldXpos)
            mnogY = -1;
        oldXpos = newXPos;



        Matr rotateMnogY = RotateMY(mnogY * ky * RAD);

        rotate = rotateMnogY * rotate;
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
    if(sizeCenter <= 0.)
        sizeCenter = 1;
    repaint();
}
