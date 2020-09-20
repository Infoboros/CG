#include <zconf.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        angle(0),
        check_delete(0) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p) {
    QWidget::paintEvent(p);
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white));

    int center_x = width() / 2;
    int center_y = height() / 2;

    painter.drawLine(center_x, 0, center_x, height());//рисуем разделительную черту

    QPointF center_l(center_x / 2., center_y);//центр левого квадрата
    QPointF center_r(center_x / 2. * 3., center_y);//центр правого квадрата

    float big_radius;
    // Вычисляем радиус внешней окружности
    if (width() / 2. > height()) // Если ширина окна больше высоты
        big_radius = (height() - 20) / 2; // Отступ от краёв - 10 пикселей
    else
        big_radius = (width() / 2. - 20) / 2;
    float small_radius = big_radius / 2.;

    //Перенос центров
    painter.translate(center_l.x(), center_l.y());

    Matr r_m = RotateM(angle);
    Matr r_m_pi = RotateM(angle + PI);

    ReflectionHM reflectionH;
    for (int i = 0; i < 2; ++i) {
        painter.setBrush(QBrush(Qt::red));
        drawStar(painter, big_radius, small_radius, r_m);
        painter.setBrush(QBrush(Qt::blue));
        drawStar(painter, big_radius, small_radius, r_m_pi);
        painter.setBrush(QBrush(Qt::white));
        drawCircle(painter, small_radius);
        painter.setBrush(QBrush(Qt::green));
        drawStar(painter, small_radius, small_radius / 2., r_m);

        r_m = reflectionH * r_m;
        r_m_pi = reflectionH * r_m_pi;
        painter.translate(width() / 2., 0);
    }
    painter.setBrush(QBrush(Qt::white));
    painter.translate(-width() / 2., 0);
    drawMini(painter, small_radius / 2., reflectionH);
    painter.translate(-width() / 2., 0);
    drawMini(painter, small_radius / 2., Matr({{1, 0, 0},
                                               {0, 1, 0},
                                               {0, 0, 1}}));

}

void MainWindow::drawCircle(QPainter &painter, double radius) {
    painter.drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void MainWindow::drawStar(QPainter &painter, double big_radius, double small_radius, Matr &pr_matr) {
    RotateM r36(PI / 5);
    RotateM r72(2 * PI / 5);
    QPointF big_back_star(0, -big_radius);
    QPointF small_back_star(0, -small_radius);
    small_back_star = r36 * small_back_star;

    QPolygonF back_star;
    for (int i = 0; i < 5; ++i) {
        back_star << pr_matr * big_back_star << pr_matr * small_back_star;
        big_back_star = r72 * big_back_star;
        small_back_star = r72 * small_back_star;
    }
    painter.drawPolygon(back_star);
}

void MainWindow::drawMini(QPainter &painter, int radius, Matr pr_m) {
    RotateM rotate(PI / 10.);
    DilatationM dilatation(0.99, 0.99);
    int randomchik = rand() % 20;
    if (!randomchik) {
        int random_figure = rand() % 2;
        int random_x = rand() % radius;
        int random_y = rand() % radius;
        int figure_radius = radius - sqrt(pow(random_x, 2) + pow(random_y, 2));
        if (figure_radius > radius / 5.)
            figure_radius = radius / 5.;

        //Квадрат
        if (random_figure == 0) {
            vector<QPointF> path = {
                    QPointF(random_x - figure_radius, random_y - figure_radius),
                    QPointF(random_x + figure_radius, random_y - figure_radius),
                    QPointF(random_x + figure_radius, random_y + figure_radius),
                    QPointF(random_x - figure_radius, random_y + figure_radius),
                    QPointF(random_x - figure_radius, random_y - figure_radius),
            };
            mini_figures.push_back(path);
        } else if (random_figure == 1) {
            vector<QPointF> path = {
                    QPointF(random_x - figure_radius, random_y - figure_radius),
                    QPointF(random_x + figure_radius, random_y - figure_radius),
                    QPointF(random_x + figure_radius, random_y + figure_radius),
            };
            mini_figures.push_back(path);
        }
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
    if (check_delete == 100) {
        mini_figures.erase(mini_figures.begin());
        check_delete = 0;
    }
}

void MainWindow::wheelEvent(QWheelEvent *wheelevent) {
    angle += wheelevent->delta() / 100;
    repaint();
    usleep(160000);
}

