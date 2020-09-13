//
// Created by ouroboros on 13.09.2020.
//

#ifndef LAB1_WORLDTOSCREENCONVERTER_H
#define LAB1_WORLDTOSCREENCONVERTER_H

#include <QtCore/QRect>

#define OFFSET 100

class WorldToScreenConverter {
public:
    WorldToScreenConverter(double x1, double x2, double y1, double y2, QRect sc)
            : x1(x1), x2(x2), y1(y1), y2(y2), screen(sc) {};
    // Экранная система координат
    QRect screen;
    // Мировая система координат
    double x1, x2, y1, y2;

    // Функция преобразует координаты точки (x, y) из мировой системы координат в экранную
    QPointF convert(double x, double y);

    // Функция преобразует значение ординаты Y из экранной системы координат в мировую
    double y(int Y);

    // Функция возвращает значение абсциссы в мировой системе координат по её значению X в экранной
    double x(int X);

    double getX1();

    double getX2();

    double getY1();

    double getY2();
};

#endif //LAB1_WORLDTOSCREENCONVERTER_H
