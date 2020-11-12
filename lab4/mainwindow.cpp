
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        c(400),
        rotate(),
        obj(Tumba(1, 50)),
        mousePosition(0, 0),
        mouseFlag(false){
    ui->setupUi(this);
    mousePosition = this->pos();
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
    QMatrix4x4 tr;
    tr.translate(0, 0, wheelevent->delta()/50.);
    obj = tr*obj;
    repaint();
}

void MainWindow::drawDinamic(QPainter &painter, double radius) {
    obj = rotate*obj;
    QMatrix4x4 proect(1., 0, 0, 0,
                      0, 1., 0, 0,
                      0, 0, 0, 0,
                      0, 0, 1/c, 1.);
    obj.draw(painter, proect);
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (mouseFlag) {
        QPoint dp = mouseEvent->pos() - mousePosition;
        //меняем вращение
        rotate = QMatrix4x4();
        rotate.rotate(-dp.x()/2., 0, 1, 0);
        rotate.rotate(dp.y()/2., 1, 0, 0);
        mousePosition = mouseEvent->pos();
        repaint();
    }
}
void MainWindow::on_pushButton_clicked()
{
    c = ui->plainTextEdit->toPlainText().toDouble()*10.;
    if (c<200)
        c = 200;
    double sH = ui->plainTextEdit_2->toPlainText().toDouble();
    if (sH>=100)
        sH = 100;
    else if (sH <= 5)
        sH = 5;
    obj = Tumba(1, sH);
    repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    mousePosition = event->pos();
    mouseFlag = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *) {
    mouseFlag = false;
}
