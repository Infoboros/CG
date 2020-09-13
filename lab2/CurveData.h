//
// Created by ouroboros on 13.09.2020.
//

#ifndef LAB1_CURVEDATA_H
#define LAB1_CURVEDATA_H

#include <QtGui/QColor>
#include <QtGui/QPen>
#include <utility>

#include <math.h>

class CurveData {
protected:
    QPen curvenPen;
public:
    explicit CurveData(QPen p):curvenPen(std::move(p)){};

    virtual double F(double) { return 0; }

    QPen getPen(){
        return curvenPen;
    }
};

class SinCurveData : public CurveData {
public:

    SinCurveData(): CurveData(QPen(Qt::red)){};
    double F(double x) override {
        return sin(x);
    }
};

class CosCurveData : public CurveData {
public:

    CosCurveData(): CurveData(QPen(Qt::blue)){};
    double F(double x) override {
        return cos(x);
    }
};

class LineCurveData : public CurveData {
public:

    LineCurveData(): CurveData(QPen(Qt::blue)){};
    double F(double x) override {
        return x;
    }
};

#endif //LAB1_CURVEDATA_H
