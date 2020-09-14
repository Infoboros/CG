//
// Created by ouroboros on 13.09.2020.
//

#ifndef LAB1_CHART_H
#define LAB1_CHART_H

#include <fstream>

using namespace std;

#include <QtWidgets/QWidget>
#include <QVector>
#include <utility>

#include "CurveData.h"
#include "WorldToScreenConverter.h"
#include "Axis.h"

#define MIN_Y -1000
#define MAX_Y 1000

class Chart : public QWidget
{
    Q_OBJECT

public:
    Chart(QWidget *parent = nullptr);
    QVector<CurveData *> curves;
    void setNewA(double a);
    void setNewB(double b);
    void reloadCurve(QString text);

private:
    WorldToScreenConverter converter;
    void paintEvent(QPaintEvent* p_event);
    void recalc();
};

#endif //LAB1_CHART_H
