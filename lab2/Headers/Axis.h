//
// Created by ouroboros on 13.09.2020.
//

#ifndef LAB1_AXIS_H
#define LAB1_AXIS_H

#include <QtGui/QPainter>
#include <QString>
#include <QStaticText>
#include "WorldToScreenConverter.h"

#include "stdio.h"

class Axis {
public:
    static void step(double &k, double &h, double &m, double &n);
    virtual void draw(QPainter &painter, WorldToScreenConverter &converter) = 0;
};

class AbscissaAxis : Axis {
public:
    void draw(QPainter &painter, WorldToScreenConverter &converter);
};

class OrdinateAxis : Axis {
public:
    void draw(QPainter &painter, WorldToScreenConverter &converter);
};

#endif //LAB1_AXIS_H
