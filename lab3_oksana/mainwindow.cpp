#include <zconf.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        angle(0),
        check_delete(0),
        start(false) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p) {
    QWidget::paintEvent(p);
    QPainter painter(this);
    painter.setPen(QPen(5));
    painter.setBrush(QBrush(Qt::white));

    int center_x = width() / 2;
    int center_y = height() / 2;

    painter.drawLine(center_x, 0, center_x, height());//рисуем разделительную черту

    QPointF center_l(center_x / 2., center_y);//центр левого квадрата

    float big_radius;
    // Вычисляем радиус внешней окружности
    if (width() / 2. > height()) // Если ширина окна больше высоты
        big_radius = (height() - 20) / 2; // Отступ от краёв - 10 пикселей
    else
        big_radius = (width() / 2. - 20) / 2;
    float small_radius = big_radius / 2.;

    //Перенос центров
    painter.translate(center_l.x(), center_l.y());

    Matr r_m = RotateM(0);

    ReflectionHM reflectionH;
    for (int i = 0; i < 2; ++i) {
        painter.setBrush(QBrush(Qt::white));
        drawAxis(painter, big_radius, r_m);
        drawFan(painter, small_radius, r_m);

        r_m = reflectionH * r_m;
        painter.translate(width() / 2., 0);
    }
}

void MainWindow::drawMini(QPainter &painter, int radius, Matr pr_m) {
    RotateM rotate(PI / 1000.);
    DilatationM dilatation(0.9999, 0.99999);
    radius -= 20;
    int randomchik = rand() % 400;
    if (!randomchik) {
        double figure_radius = radius / 5;
        double random_x = rand() % (radius - radius / 5);
        double random_y = rand() % (radius - radius / 5);
        vector<QPointF> path = {
                QPointF(random_x, random_y - figure_radius),
                QPointF(random_x + figure_radius / 5., random_y - figure_radius / 5.),
                QPointF(random_x + figure_radius, random_y),
                QPointF(random_x + figure_radius / 5., random_y + figure_radius / 5.),
                QPointF(random_x, random_y + figure_radius),
                QPointF(random_x - figure_radius / 5., random_y + figure_radius / 5.),
                QPointF(random_x - figure_radius, random_y),
                QPointF(random_x - figure_radius / 5., random_y - figure_radius / 5.),
                QPointF(random_x, random_y - figure_radius)
        };
        mini_figures.push_back(path);
    }


    for (auto &figure: mini_figures) {
        QPolygonF polygon;
        for (auto &p:figure) {
            p = rotate * p;
            p = dilatation * p;
            polygon << pr_m * p;
        }
        painter.drawPolygon(polygon);
    }
    check_delete++;
    if (check_delete == 1000) {
        if (!mini_figures.empty())
            mini_figures.erase(mini_figures.begin());
        check_delete = 0;
    }
}

void MainWindow::drawAxis(QPainter &painter, double radius, Matr r_m) {
    QRectF main_rect(-radius, -radius, 2 * radius, 2 * radius);

    double found_w = radius / 3.;
    double found_h = radius / 10.;

    QRectF found(-found_w, radius - 2 * found_h, 2 * found_w, 2 * found_h);

    QPointF center_green_circle(found_w / 2., radius - found_h);
    center_green_circle = r_m * center_green_circle;
    double radius_green_circle(found_h / 2.);

    QRectF axis(-radius / 60., 0, radius / 30., radius - 2 * found_h);


    painter.drawRect(main_rect);

    painter.setBrush(QBrush(Qt::cyan));
    drawMini(painter, radius, r_m);

    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(found);

    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(axis);
    if (start)
        painter.setBrush(QBrush(Qt::green));
    else
        painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(center_green_circle, radius_green_circle, radius_green_circle);
    painter.setBrush(QBrush(Qt::white));
}

void MainWindow::drawFan(QPainter &painter, double radius, Matr r_m) {
    vector<QColor> brash_set({Qt::red, Qt::yellow, Qt::green, Qt::blue, Qt::magenta});
    for (int i = 0; i < 5; ++i) {
        painter.setBrush(QBrush(brash_set[i]));
        painter.drawPie(-radius, -radius, 2 * radius, 2 * radius, 2 * 36 * 16 * i + angle, 36 * 16);
    }
    angle *= -1;
    double radius_black_circle = radius / 5.;
    painter.setBrush(QBrush(Qt::black));
    painter.drawEllipse(-radius_black_circle, -radius_black_circle, 2 * radius_black_circle, 2 * radius_black_circle);

}


void MainWindow::on_pushButton_clicked() {
    start = !start;
    if (!start)
        ui->pushButton->setText("Start");
    else
        ui->pushButton->setText("Stop");
    while (start) {
        QApplication::processEvents();
        angle += 1;
        repaint();
    }
}
