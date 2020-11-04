//
// Created by ouroboros on 02.10.2020.
//

#ifndef LAB1_MODEL3D_H
#define LAB1_MODEL3D_H

#include <QPainter>
#include <iostream>
#include "afin3d.h"


#define S_R 26
#define U_Y -60

#define RAD 3.14/180.

class Point3D {
public:
    Point3D(double x, double y, double z) : point({x, y, z, 1}) {};

    Point3D(type_arr vec) : point(vec) {};
    type_arr point;

    double x();

    double y();

    double z();
};

class Model {
protected:
    vector<Point3D> vectorPoints;
public:
    explicit Model(vector<Point3D> vector) : vectorPoints(std::move(vector)) {};

    friend Model operator*(Matr &, Model &);

    void draw(QPainter &painter);
};

class SixFigure : public Model{
public:
    SixFigure(double radius);
};

class Object {
protected:
    vector<Model> vectorModels;
public:
    explicit Object(vector<Model> vector) : vectorModels(std::move(vector)) {};

    friend Object operator*(Matr, Object &);

    void draw(QPainter &painter);
    void drawFront(QPainter &painter);
    void drawPorf(QPainter &painter);
    void drawUp(QPainter &painter);
};

class Lampa : public Object{
private:
    double getRadiusSix(double y);
public:
    Lampa(double k);
};

#endif //LAB1_MODEL3D_H
