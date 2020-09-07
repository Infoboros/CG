#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    angle = 0;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this); // Создаём объект-живописец

    QColor purpl(123, 104, 238); // Фиолетовый
    QPen Pen(Qt::black, 5, Qt::SolidLine);

    // Радиус большей окружности
    float radius;
    // Вычисляем радиус окружности
    if (width() > height()) // Если ширина окна больше высоты
     radius = (height() - 20) / 2; // Отступ от краёв - 10 пикселей
    else radius = (width() - 20) / 2;

    // Координаты центра всего
    QPointF center = QPointF(width() / 2, height() / 2);

    //Задаем настройки для вращения
    painter.translate(center.x(), center.y());
    painter.rotate(angle);

    // Задаём область прорисовки круга
    QRectF rect = QRectF(-radius, -radius, radius*2, radius*2);

    // Рисуем большой круг красно-оранжевым цветом
    painter.setBrush(purpl);
    painter.setPen(Pen);
    painter.drawEllipse(rect);

    painter.setBrush(QBrush());

    //Больщой квадрат
    painter.setBrush(QBrush(Qt::blue));
    float aBigRect = radius*sqrt(2);
    QRectF bigRect = QRectF(- aBigRect/2.,-aBigRect/2., aBigRect, aBigRect);
    painter.drawRect(bigRect);

    //Четыре маленькие окружности
    painter.setBrush(QBrush(Qt::red));
    float bigRectRadius = aBigRect/2;
    QRectF smallLeftsTopsRect = QRectF(-bigRectRadius, -bigRectRadius, bigRectRadius, bigRectRadius);//Маленький квадратик слева вверху
    for (int i = 0; i < 4; ++i) {
        painter.drawEllipse(smallLeftsTopsRect);
        painter.rotate(90);
    }

    //Четыре маленьких ромбика
    float heightR = (radius - aBigRect) / 2.;
    float widthR = aBigRect/2.;
    QPointF leftTopR = QPointF(-widthR/2., bigRectRadius/2. + radius/2. - heightR/2.);
    QPointF pathRomb[5] = {
                            QPointF(leftTopR.x(), leftTopR.y() + heightR/2.),
                            QPointF(leftTopR.x() + widthR/2., leftTopR.y()),
                            QPointF(leftTopR.x() + widthR, leftTopR.y() + heightR/2.),
                            QPointF(leftTopR.x() + widthR/2., leftTopR.y() + heightR),
                            QPointF(leftTopR.x(), leftTopR.y() + heightR/2.),
    };
    for (int i = 0; i < 4; ++i) {
        QPainterPath rombPathPainter;
        rombPathPainter.moveTo(pathRomb[0]);
        for (int path = 0; path < 5; ++path) {
            rombPathPainter.lineTo(pathRomb[path]);
        };
        painter.drawPath(rombPathPainter);
        painter.rotate(90);
    }

    //Маленький круг
    painter.setBrush(QBrush(Qt::blue));
    float smallCircleRadius = aBigRect/4;
    QRectF smallCircleRect = QRectF(-smallCircleRadius, -smallCircleRadius, smallCircleRadius*2, smallCircleRadius*2);
    painter.drawEllipse(smallCircleRect);

    //Маленький квадрат
    painter.setBrush(QBrush(Qt::red));
    float aSmallRect = aBigRect/(2*sqrt(2));
    QRectF smallRect = QRectF(- aSmallRect/2.,-aSmallRect/2., aSmallRect, aSmallRect);
    painter.rotate(45); //он должен быть перпендикулярен большому
    painter.drawRect(smallRect);

}


// Обработчик события прокрутки колеса мыши
void MainWindow::wheelEvent(QWheelEvent* wheelevent)
{
    angle += wheelevent->delta() / 10;
    repaint(); // Обновляем окно
}
