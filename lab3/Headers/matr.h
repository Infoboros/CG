#ifndef LAB1_MATR_H
#define LAB1_MATR_H

#include <utility>
#include <vector>

using namespace std;

typedef vector<double> type_arr;
typedef vector<type_arr> type_m;

class Matr{
private:
    type_m m;

public:
    explicit Matr(type_m m): m(std::move(m)){};
    int get_n();
    int get_m();
    friend Matr operator *(Matr &m_l, Matr &m_r);
    friend type_arr operator *(Matr &m, type_arr &arr);
    type_arr & operator [](int index);
};

#endif //LAB1_MATR_H
