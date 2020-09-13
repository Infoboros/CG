//
// Created by ouroboros on 13.09.2020.
//

#ifndef LAB1_CHART_H
#define LAB1_CHART_H

#include <QtWidgets/QWidget>
#include <QVector>
#include <utility>

#include "CurveData.h"
#include "WorldToScreenConverter.h"
#include "Axis.h"

#define MIN_Y -100
#define MAX_Y 100

class Chart : public QWidget
{
    Q_OBJECT

public:
    Chart(QWidget *parent = nullptr);
    QVector<CurveData *> curves;

private:
    WorldToScreenConverter converter;
    void paintEvent(QPaintEvent* p_event);

};

#endif //LAB1_CHART_H
