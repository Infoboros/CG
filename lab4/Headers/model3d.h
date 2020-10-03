//
// Created by ouroboros on 02.10.2020.
//

#ifndef LAB1_MODEL3D_H
#define LAB1_MODEL3D_H

#include <QPainter>
#include <iostream>
#include "afin3d.h"


#define LEN_X 70*k
#define LEN_Y LEN_X/12.
#define LEN_Z LEN_X

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
private:
    vector<Point3D> vectorPoints;
public:
    explicit Model(vector<Point3D> vector) : vectorPoints(std::move(vector)) {};

    friend Model operator*(Matr &, Model &);

    void draw(QPainter &painter);
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
        Matr rt_y_90 = RotateMY(90.*RAD);
        Matr t_up = TranslateM(0, -20*LEN_Y, 0);
        Matr t_down = TranslateM(0, 20*LEN_Y, 0);
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
        Matr t_back = TranslateM(0, 0, -2*LEN_Z);
        Matr t_rigth = TranslateM(2*(LEN_X+LEN_Y), 0, 0);
        for (int i = 0; i < 2; ++i) {
            vectorModels.push_back(outSquareL);
            vectorModels.push_back(t_rigth*outSquareL);
            outSquareL = t_back*outSquareL;
        }

        Model outSquareS({Point3D(-LEN_X-2, 21*LEN_Y, -LEN_Z),
                          Point3D(-(LEN_X+LEN_Y*2), 21*LEN_Y, -LEN_Z),
                          Point3D(-(LEN_X+LEN_Y*2), 21*LEN_Y, LEN_Z),
                          Point3D(-LEN_X-2, 21*LEN_Y, LEN_Z)});
        Matr t_up_s = TranslateM(0, -42*LEN_Y, 0);
        for (int i = 0; i < 2; ++i) {
            vectorModels.push_back(outSquareS);
            vectorModels.push_back(t_up_s*outSquareS);
            outSquareS = t_rigth*outSquareS;
        }




    };
};

#endif //LAB1_MODEL3D_H
