//
// Created by ouroboros on 20.09.2020.
//
#include "../Headers/matr.h"


Matr operator*(Matr &m_l, Matr &m_r) {
    type_m result;
    for (int i = 0; i < m_l.get_n(); ++i) {
        result.push_back({});
        for (int j = 0; j < m_r.get_m(); ++j) {
            double i_j_el = 0;
            for (int k = 0; k < m_r.get_n(); ++k) {
                i_j_el += m_l[i][k] * m_r[k][j];
            }
            result[i].push_back(i_j_el);
        }
    }
    return Matr(result);
}

type_arr operator*(Matr &m, type_arr &arr) {
    type_arr result;

    for (int i = 0; i < m.get_n(); ++i) {
        double i_j_el = 0;
        for (int j = 0; j < arr.size(); ++j)
            i_j_el += m[i][j] * arr[j];

        result.push_back(i_j_el);
    }

    return result;
}

type_arr &Matr::operator[](int index) {
    return m[index];
}

int Matr::get_n() {
    return m.size();
}

int Matr::get_m() {
    return m[0].size();
}

QPointF operator*(Matr &m, QPointF &p) {
    type_arr mult_arr({p.x(), p.y()});
    for (int i = 2; i < m.get_n(); ++i)
        mult_arr.push_back(0);
    type_arr tranfrom_arr = m*mult_arr;
    return {tranfrom_arr[0], tranfrom_arr[1]};
}
