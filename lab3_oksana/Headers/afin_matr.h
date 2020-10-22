#ifndef LAB1_AFIN_MATR_H
#define LAB1_AFIN_MATR_H

#include "matr.h"
#include "math.h"

#define PI 3.14
#define RAD PI/180.
class RotateM : public Matr {
public:
    explicit RotateM(double alfa) :
            Matr({
                         {cos(alfa), -sin(alfa), 0},
                         {sin(alfa), cos(alfa),  0},
                         {0,         0,          1}
                 }) {};
};

class TranslateM : public Matr {
public:
    explicit TranslateM(double x, double y) :
            Matr({
                         {1, 0, 0},
                         {0, 1, 0},
                         {x, y, 1}
                 }) {};
};

class DilatationM : public Matr {
public:
    explicit DilatationM(double kx, double ky) :
            Matr({
                         {kx, 0, 0},
                         {0, ky, 0},
                         {0, 0, 1}
                 }) {};
};

class ReflectionVM : public Matr {
public:
    explicit ReflectionVM() :
            Matr({
                         {1, 0, 0},
                         {0, -1, 0},
                         {0, 0, 1}
                 }) {};
};

class ReflectionHM : public Matr {
public:
    explicit ReflectionHM() :
            Matr({
                         {-1, 0, 0},
                         {0, 1, 0},
                         {0, 0, 1}
                 }) {};
};
#endif //LAB1_AFIN_MATR_H
