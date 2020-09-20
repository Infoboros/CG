#include "mainwindow.h"
#include <QApplication>

#include "Headers/matr.h"

int main(int argc, char *argv[]) {
    Matr m1({{3, -1, 2},
             {4, 2, 0},
             {-5, 6, 1}});
    Matr m2({{8, 1},
             {7, 2},
             {2, -3}});
    type_arr vec({8, 7, 2});

    Matr m3 = m1*m2;
    type_arr vec_res = m1*vec;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
