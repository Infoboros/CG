//
// Created by ouroboros on 20.09.2020.
//

#ifndef LAB1_AFIN3D_H
#define LAB1_AFIN3D_H

#include "matr.h"
#include "math.h"

class RotateMX : public Matr {
public:
    explicit RotateMX(double alfa) :
            Matr({
                         {1, 0,         0,          0},
                         {0, cos(alfa), -sin(alfa), 0},
                         {0, sin(alfa), cos(alfa),  0},
                         {0, 0,         0,          1}
                 }) {};
};

class RotateMY : public Matr {
public:
    explicit RotateMY(double alfa) :
            Matr({
                         {cos(alfa), 0, -sin(alfa), 0},
                         {0,         1, 0,          0},
                         {sin(alfa), 0, cos(alfa),  0},
                         {0,         0, 0,          1}
                 }) {};
};

class RotateMZ : public Matr {
public:
    explicit RotateMZ(double alfa) :
            Matr({
                         {cos(alfa),  sin(alfa), 0, 0},
                         {-sin(alfa), cos(alfa), 0, 0},
                         {0,          0,         1, 0},
                         {0,          0,         0, 1}
                 }) {};
};

class DilatationM : public Matr {
public:
    explicit DilatationM(double kx, double ky, double kz) :
            Matr({
                         {kx, 0,  0,  0},
                         {0,  ky, 0,  0},
                         {0,  0,  kz, 0},
                         {0,  0,  0,  1}
                 }) {};
};

class TranslateM : public Matr {
public:
    explicit TranslateM(double x, double y, double z) :
            Matr({
                         {1, 0,  0,  x},
                         {0,  1, 0,  y},
                         {0,  0,  1, z},
                         {0,  0,  0,  1}
                 }) {};
};

#endif //LAB1_AFIN3D_H
