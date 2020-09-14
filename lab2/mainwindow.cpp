#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *p) {
    QWidget::paintEvent(p);
}

void MainWindow::on_aBox_valueChanged(double a)
{
    ui->centralwidget->setNewA(a);
    ui->centralwidget->repaint();
}

void MainWindow::on_bBox_valueChanged(double b)
{
    ui->centralwidget->setNewB(b);
    ui->centralwidget->repaint();
}
void MainWindow::on_pushButton_clicked()
{
    ui->centralwidget->reloadCurve(ui->plainTextEdit->toPlainText());
}
