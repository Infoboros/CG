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
    explicit Model(vector<Point3D> vector) : vectorPoints(std::move(vector)) {};

    friend Model operator*(QMatrix4x4 &, Model &);

    void draw(QPainter &painter);
};

class Object {
protected:
    vector<Model> vectorModels;
public:
    explicit Object(vector<Model> vector) : vectorModels(std::move(vector)) {};

    friend Object operator*(QMatrix4x4, Object &);

    void draw(QPainter &painter);
    void drawFront(QPainter &painter);
    void drawPorf(QPainter &painter);
    void drawUp(QPainter &painter);
};

class Tumba : public Object {
public:
    Tumba(double k, double sizeH) :
            Object({}) {
        Model inSquare({Point3D(-LEN_X, -LEN_Y, LEN_Z),
                        Point3D(LEN_X, -LEN_Y, LEN_Z),
                        Point3D(LEN_X, LEN_Y, LEN_Z),
                        Point3D(-LEN_X, LEN_Y, LEN_Z)});
        Model centerSquare({Point3D(-LEN_X, -sizeH*k, LEN_Z),
                            Point3D(LEN_X, -sizeH*k, LEN_Z),
                            Point3D(LEN_X, sizeH*k, LEN_Z),
                            Point3D(-LEN_X, sizeH*k, LEN_Z)});
        QMatrix4x4 rt_y_90, t_up, t_down;
        rt_y_90.rotate(90*RAD, 0, 1, 0);
        t_up.translate(0, -20*LEN_Y, 0);
        t_down.translate(0, 20*LEN_Y, 0);
        for (int i = 0; i < 4; ++i) {
            vectorModels.push_back(centerSquare);
            vectorModels.push_back(t_up*inSquare);
            vectorModels.push_back(t_down*inSquare);
            inSquare = rt_y_90*inSquare;
            centerSquare = rt_y_90*centerSquare;
        }

        Model outSquareL({Point3D(-LEN_X-2, -21*LEN_Y, LEN_Z),
                          Point3D(-(LEN_X+LEN_Y*2), -21*LEN_Y, LEN_Z),
                          Point3D(-(LEN_X+LEN_Y*2), 21*LEN_Y, LEN_Z),
                          Point3D(-LEN_X-2, 21*LEN_Y, LEN_Z)});
        QMatrix4x4 t_back, t_rigth;
        t_back.translate(0, 0, -2*LEN_Z);
        t_rigth.translate(2*(LEN_X+LEN_Y), 0, 0);
        for (int i = 0; i < 2; ++i) {
            vectorModels.push_back(outSquareL);
            vectorModels.push_back(t_rigth*outSquareL);
            outSquareL = t_back*outSquareL;
        }

        Model outSquareS({Point3D(-LEN_X-2, 21*LEN_Y, -LEN_Z),
                          Point3D(-(LEN_X+LEN_Y*2), 21*LEN_Y, -LEN_Z),
                          Point3D(-(LEN_X+LEN_Y*2), 21*LEN_Y, LEN_Z),
                          Point3D(-LEN_X-2, 21*LEN_Y, LEN_Z)});
        QMatrix4x4 t_up_s;
        t_up_s.translate(0, -42*LEN_Y, 0);
        for (int i = 0; i < 2; ++i) {
            vectorModels.push_back(outSquareS);
            vectorModels.push_back(t_up_s*outSquareS);
            outSquareS = t_rigth*outSquareS;
        }

    };
};

#endif //LAB1_MODEL3D_H
