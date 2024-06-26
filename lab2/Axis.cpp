//
// Created by ouroboros on 13.09.2020.
//

#include "Axis.h"
#include <cmath>

void Axis::step(double &k, double &h, double &m, double &n) {
    double p = h / k;

    double n1 = trunc(log10(p));
    double n2 = trunc(log10(p / 2.));
    double n5 = trunc(log10(p / 5.));

    double minK, minH, minM, minN;

    double min = 9999999999;

    if ((p - pow(10, n1)) < min) {
        minH = k * (p - pow(10, n1));
        minM = 1;
        minK = minM * pow(10, n1);
        minN = n1;
        min = (p - pow(10, n1));
    }

    if ((-p + pow(10, n1)) < min) {
        minH = k * (-p + pow(10, n1));
        minM = 1;
        minK = minM * pow(10, n1);
        minN = n1;
        min = (-p + pow(10, n1));
    }

    if ((p - 2. * pow(10, n2)) < min) {
        minH = k * (p - 2. * pow(10, n2));
        minM = 2;
        minK = minM * pow(10, n2);
        minN = n2;
        min = (p - 2. * pow(10, n2));
    }

    if ((-p + 2. * pow(10, n2)) < min) {
        minH = k * (-p + 2. * pow(10, n2));
        minM = 2;
        minK = minM * pow(10, n2);
        minN = n2;
        min = (-p + 2. * pow(10, n2));
    }

    if ((p - 5. * pow(10, n5)) < min) {
        minH = k * (p - 5. * pow(10, n5));
        minM = 5;
        minK = minM * pow(10, n5);
        minN = n5;
        min = (p - 5. * pow(10, n5));
    }

    if ((-p + 5. * pow(10, n5)) < min) {
        minH = k * (-p + 5. * pow(10, n5));
        minM = 5;
        minK = minM * pow(10, n5);
        minN = n5;
        min = (-p + 5. * pow(10, n5));
    }

    k = minK;
    h = minH;
    m = minM;
    n = minN;
}

void AbscissaAxis::draw(QPainter &painter, WorldToScreenConverter &converter) {
    double offset = 0;
    if (converter.y1 > 0)
        offset = converter.y1;
    QPointF startR(converter.x1, offset);
    QPointF endR(converter.x2, offset);

    painter.drawLine(converter.convert(startR.x(), startR.y()),
                     converter.convert(endR.x(), endR.y()));

    double k = (converter.getX2() - converter.getX1()) / (converter.x2 - converter.x1);
    double h = (converter.getX2() - converter.getX1()) / 40.;
    double m, n;

    step(k, h, m, n);
    currentStep = k;
    double radiusW = k / 100.;
    double radiusH = (converter.y2 - converter.y1) / 50.;
    bool flag = true;
    double start = floor(converter.x1 / k);
    for (double x = start * k +k; x <= converter.x2; x += k) {

        QPointF leftTop = converter.convert(x - radiusW, radiusH);
        QPointF rightBot = converter.convert(x + radiusW, -radiusH);
        painter.drawRect(QRectF(leftTop, rightBot));

        char buf[80];
        sprintf(buf, "%7.2e", x);
        QString text(buf);
        if (flag) {
            QPointF textLeftTop = converter.convert(x - radiusW * 200, radiusH * 3);
            QPointF textRightBot = converter.convert(x + radiusW * 200, radiusH);
            painter.setFont(QFont("", (textLeftTop.x() - textRightBot.x()) / text.length()));
            painter.drawText(QRectF(textLeftTop, textRightBot), Qt::AlignCenter, text);
        } else {
            QPointF textLeftTop = converter.convert(x - radiusW * 200, -radiusH);
            QPointF textRightBot = converter.convert(x + radiusW * 200, -radiusH * 5);
            painter.setFont(QFont("", (textLeftTop.x() - textRightBot.x()) / text.length()));
            painter.drawText(QRectF(textLeftTop, textRightBot), Qt::AlignCenter, text);
        }
        flag = !flag;
    }

}

void OrdinateAxis::draw(QPainter &painter, WorldToScreenConverter &converter) {
    double offset = 0;
    if (converter.x1 > 0)
        offset = converter.x1;
    if (converter.x2 < 0)
        offset = converter.x2;
    QPointF startR(offset, converter.y1);
    QPointF endR(offset, converter.y2);

    painter.drawLine(converter.convert(startR.x(), startR.y()),
                     converter.convert(endR.x(), endR.y()));

    double k = (converter.getY2() - converter.getY1()) / (converter.y2 - converter.y1);
    double h = (converter.getY2() - converter.getY1()) / 45.;
    double m, n;

    step(k, h, m, n);
    currentStep = k;
    double radiusW = k / 100.;
    double radiusH = (converter.x2 - converter.x1) / 100.;

    double start = floor(converter.y1 / k);
    for (double y = start*k+k; y <= converter.y2; y += k) {
        QPointF leftTop = converter.convert(-radiusH + offset, y + radiusW);
        QPointF rightBot = converter.convert(+radiusH + offset, y - radiusW);
        painter.drawRect(QRectF(leftTop, rightBot));

        char buf[80];
        sprintf(buf, "%7.2e", y);
        QString text(buf);

        QPointF textLeftTop = converter.convert(-radiusH * 10 + offset, y + radiusW * 50);
        QPointF textRightBot = converter.convert(-radiusH + offset, y - radiusW * 50);
        painter.setFont(QFont("", (textLeftTop.x() - textRightBot.x()) / text.length()));
        painter.drawText(QRectF(textLeftTop, textRightBot), Qt::AlignRight|Qt::AlignVCenter, text);
    }
}
