//
// Created by ouroboros on 02.10.2020.
//

#ifndef LAB1_MODEL3D_H
#define LAB1_MODEL3D_H

#include <QPainter>
#include <iostream>
#include <QVector3D>
#include <QMatrix4x4>

using namespace std;

#define LEN_X 70*k
#define LEN_Y LEN_X/12.
#define LEN_Z LEN_X

#define CH_L_a 50
#define CH_L_b 5
#define CH_D 50

#define RAD 1

class Point3D {
public:
    Point3D(double x, double y, double z) : point(x, y, z) {};

    Point3D(QVector3D vec) : point(vec) {};
    QVector3D point;

    double x();

    double y();

    double z();
};

class Model {
private:
    vector<Point3D> vectorPoints;
public:
    explicit Model(vector<Point3D> vector, QColor c) : vectorPoints(std::move(vector)), color(c) {};
    QColor color;

    friend Model operator*(QMatrix4x4 &, Model &);
    friend bool operator>(Model &, Model &);

    Point3D getBariCenter();
    void draw(QPainter &painter);
};

class Object {
public:
    explicit Object(vector<Model> vector) : vectorModels(std::move(vector)) {};

    friend Object operator*(QMatrix4x4, Object &);

    void draw(QPainter &painter, QMatrix4x4 proec);

    vector<Model> vectorModels;
};

class Tumba : public Object {
public:
    Tumba(double k, double sizeH);;
};

class Chear : public Object{
public:
    Chear();
};

#endif //LAB1_MODEL3D_H
