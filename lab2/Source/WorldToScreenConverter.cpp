//
// Created by ouroboros on 13.09.2020.
//

#include "../Headers/WorldToScreenConverter.h"

QPointF WorldToScreenConverter::convert(double x, double y) {
    double X2 = getX2();
    double X1 = getX1();

    double Y2 = getY2();
    double Y1 = getY1();

    double X = (X2 - X1) * ((x - x1) / (x2 - x1)) + X1;
    double Y = Y2 - (Y2 - Y1) * ((y - y1) / (y2 - y1));

    return {X, Y};
}

double WorldToScreenConverter::y(int Y) {
    double Y1 = getY1();
    double Y2 = getY2();

    return (Y * (y2 - y1) + Y1 * y1 - Y2 * y2) / (Y1 - Y2);
}

double WorldToScreenConverter::x(int X) {
    double X1 = getX1();
    double X2 = getX2();

    return (X * (x2 - x1) + X2 * x1 - X1 * x2) / (X2 - X1);
}

double WorldToScreenConverter::getX1() {
    return screen.left() + OFFSET;
}

double WorldToScreenConverter::getX2() {
    return screen.right() - OFFSET;
}

double WorldToScreenConverter::getY1() {
    return screen.top() + OFFSET;
}

double WorldToScreenConverter::getY2() {
    return screen.bottom() - OFFSET;
}
