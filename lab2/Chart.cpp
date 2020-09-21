//
// Created by ouroboros on 13.09.2020.
//

#include <QtGui/QPainter>
#include "Chart.h"


Chart::Chart(QWidget *parent)
        : QWidget(parent),
        curves({new SinCurveData(), new CosCurveData(), new LineCurveData()}),
        converter(0, 20, 0, 0, parent->rect()){
    recalc();
    flag = true;
}

void Chart::paintEvent(QPaintEvent *p_event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);

    converter.screen = rect();

    AbscissaAxis abscissaAxis;
    abscissaAxis.draw(painter, converter);

    OrdinateAxis ordinateAxis;
    ordinateAxis.draw(painter, converter);

    for(auto &curve:curves){
        painter.setPen(curve->getPen());
        double step = abscissaAxis.currentStep;
        if (flag)
            step /=10000;
        QPointF oldP(converter.x1, curve->F(converter.x1));
        QPointF newP;

        for (double x = converter.x1; x <= converter.x2 + step*2; x += step) {
            painter.drawLine(converter.convert(oldP.x(), oldP.y()),
                             converter.convert(newP.x(), newP.y()));
            oldP = newP;
            newP = QPointF(x, curve->F(x));
        }
    }
}

void Chart::recalc() {
    double minY = 9999999;
    double maxY = -9999999;
    for (auto & curve : curves){
        for (double x = converter.x1; x < converter.x2; ++x) {
            double result = curve->F(x);
            if (result < minY)
                minY = result;
            if (result > maxY)
                maxY = result;
        }
    }

    if ((maxY - minY) < 0.0001)
        maxY += 1.;

    if (minY < MIN_Y)
        minY = MIN_Y;
    if (maxY > MAX_Y)
        maxY = MAX_Y;

    converter.y1 = minY;
    converter.y2 = maxY;
}

void Chart::setNewA(double a) {
    if (a < converter.x2)
        converter.x1 = a;
    recalc();
}

void Chart::setNewB(double b) {
    if (b > converter.x1)
        converter.x2 = b;
    recalc();
}

void Chart::reloadCurve(QString text) {
    curves.clear();
    flag = false;
    for(auto curve: text.split('\n'))
        curves.append(new TextCurveData(curve));
    repaint();
}
