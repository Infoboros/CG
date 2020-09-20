//
// Created by ouroboros on 20.09.2020.
//

#ifndef LAB1_AFIN_MATR_H
#define LAB1_AFIN_MATR_H

#include "matr.h"
#include "math.h"

class RotateM : Matr {
public:
    explicit RotateM(double alfa) :
            Matr({
                         {cos(alfa), -sin(alfa), 0},
                         {sin(alfa), cos(alfa),  0},
                         {0,         0,          1}
                 }) {};
};

class TranslateM : Matr {
public:
    explicit TranslateM(double x, double y) :
            Matr({
                         {1, 0, x},
                         {0, 1, y},
                         {0, 0, 1}
                 }) {};
};

class DilatationM : Matr {
public:
    explicit DilatationM(double kx, double ky) :
            Matr({
                         {kx, 0, 0},
                         {0, ky, 0},
                         {0, 0, 1}
                 }) {};
};

class ReflectionM : Matr {
public:
    explicit ReflectionM(double kx, double ky) :
            Matr({
                         {1, 0, 0},
                         {0, -1, 0},
                         {0, 0, 1}
                 }) {};
};
#endif //LAB1_AFIN_MATR_H
