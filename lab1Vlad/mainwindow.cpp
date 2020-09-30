#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :

        QMainWindow(parent),

        ui(new Ui::MainWindow),
        angle(0){

    ui->setupUi(this);

}

MainWindow::~MainWindow() {

    delete ui;

}

void MainWindow::paintEvent(QPaintEvent *event) {

    QPainter painter(this); // Создаём объект-живописец

    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    QColor lightgreen(72, 190, 142);//светло - зеленый

    QColor midBlack(0, 0, 0);

    QColor ind(0, 0, 0);

    QColor flower(8, 217, 141);//подобие светло голубого

    QPen pen;

    pen.setWidth(6);

    pen.setBrush(midBlack);

    painter.setPen(pen);

//диагональ квадрата

    float radius1;

    if (width() > height()) // Если ширина окна больше высоты

        radius1 = (height() - 20) / 2; // Отступ от краёв - 10 пикселей

    else radius1 = (width() - 20) / 2;

    if (width() < 30 || height() < 30)

        return;
    float radius2 = radius1 / 3;

    QPointF center = QPointF(width() / 2, height() / 2);

    painter.setBrush(ind);

    painter.drawEllipse(center, radius1, radius1);

    double ang = -36 * M_PI / 180.;

    painter.translate(center.x(), center.y());
    painter.rotate(18+angle);

    QPointF a(0, -radius1);
    QPolygonF poly1;

    QPointF b(0, -radius2);
    QPolygonF poly2;

    QPointF upL(a);
    QVector<QLineF> lineVec;
    for (int i = 0; i < 10; ++i) {
        poly1 << a;
        a = QPointF(a.x() * cos(ang) - a.y() * sin(ang),
                    a.x() * sin(ang) + a.y() * cos(ang));

        poly2 << b;
        b = QPointF(b.x() * cos(ang) - b.y() * sin(ang),
                    b.x() * sin(ang) + b.y() * cos(ang));

        lineVec.push_back(QLineF(upL, b));
        upL = a;
    }

    painter.setBrush(lightgreen);
    painter.drawPolygon(poly1);

    painter.setBrush(flower);
    painter.drawPolygon(poly2);

    for (auto line: lineVec)
        painter.drawLine(line);
}

// Обработчик события прокрутки колеса мыши

void MainWindow::wheelEvent(QWheelEvent *wheelevent) {

    angle -= wheelevent->delta() / 0.1;

    repaint(); // Обновляем окно

}