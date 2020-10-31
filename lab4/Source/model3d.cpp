//
// Created by ouroboros on 02.10.2020.
//
#include "../Headers/model3d.h"

Model operator*(QMatrix4x4 &matr, Model &model) {
    vector<Point3D> newVec;
    for (auto &vec: model.vectorPoints)
        newVec.emplace_back(matr * vec.point);
    return Model(newVec, model.color);
}

void Model::draw(QPainter &painter) {
    size_t size = vectorPoints.size();
    QPolygonF polygon;
    for (int i = 0; i < size; ++i)
        polygon << QPointF(vectorPoints[i].x(), vectorPoints[i].y());
    painter.setBrush(QBrush(color));
    painter.drawPolygon(polygon);

}

bool operator>(Model &f, Model &s) {
//    Point3D E_f = f.getBariCenter();
//    vector<Point3D> vec(s.vectorPoints);
//    double a11, a12,
//            a21, a22, a23,
//            a31, a32, a33;
//    a11 = E_f.x() - vec[0].x();
//    a12 = E_f.y() - vec[0].y();
//
//    a21 = vec[1].x() - vec[0].x();
//    a22 = vec[1].y() - vec[0].y();
//    a23 = vec[1].z() - vec[0].z();
//
//    a31 = vec[2].x() - vec[0].x();
//    a32 = vec[2].y() - vec[0].y();
//    a33 = vec[2].z() - vec[0].z();
//
//    double z = (-a11 * a22 * a33 - a12 * a23 * a31 + a12 * a21 * a33 + a11 * a23 * a32) / (a21 * a32 - a31 * a22) +
//               vec[0].z();
    return f.getBariCenter().z() > s.getBariCenter().z();
}

Point3D Model::getBariCenter() {
    int size = vectorPoints.size();
    double x, y, z;
    x = y = z = 0;

    for (auto &p : vectorPoints) {
        x += p.x();
        y += p.y();
        z += p.z();
    }

    return {x / size, y / size, z / size};
}

Object operator*(QMatrix4x4 matr, Object &object) {
    vector<Model> newVec;
    for (auto &model: object.vectorModels)
        newVec.push_back(matr * model);
    return Object(newVec);
}

void Object::draw(QPainter &painter, QMatrix4x4 proec) {
    vector<Object> sort_vec;
    for (int i = 0; i < vectorModels.size() - 1; ++i) {
        Model max(vectorModels[i]);
        int max_index = i;
        for (int j = i + 1; j < vectorModels.size(); ++j)
            if (vectorModels[j] > max) {
                max = vectorModels[j];
                max_index = j;
            }
        swap(vectorModels[i], vectorModels[max_index]);

    }
    for (auto &model: vectorModels)
        (proec * model).draw(painter);
}

double Point3D::x() {
    return point[0];
}

double Point3D::y() {
    return point[1];
}

double Point3D::z() {
    return point[2];
}

Chear::Chear() : Object({}) {
//    формируем стенки ножек и другие грани
    Object leg({});
    Model leg_b({
                        Point3D(-CH_L_b, -CH_L_a, CH_L_b),
                        Point3D(CH_L_b, -CH_L_a, CH_L_b),
                        Point3D(CH_L_b, CH_L_a, CH_L_b),
                        Point3D(-CH_L_b, CH_L_a, CH_L_b),
                }, Qt::green);
    Model leg_u({
                        Point3D(-CH_L_b, -CH_L_a, -CH_L_b),
                        Point3D(CH_L_b, -CH_L_a, -CH_L_b),
                        Point3D(CH_L_b, -CH_L_a, CH_L_b),
                        Point3D(-CH_L_b, -CH_L_a, CH_L_b),
                }, Qt::red);

    QMatrix4x4 r_90, leg_d, leg_2_start;
    r_90.rotate(90, 0, 1, 0);
    leg_d.translate(0, 2 * CH_L_a, 0);
//    опускаем и выносим ножку на нужное место
    leg_b = leg_d * leg_b;
    leg_u = leg_d * leg_u;
    leg_2_start.translate(CH_D, 0, CH_D);

//    крутим грани ножки что бы сформировать ее полностью
    for (int i = 0; i < 4; ++i) {
        leg.vectorModels.push_back(leg_2_start * leg_b);
        leg_b = r_90 * leg_b;
    }
    leg.vectorModels.push_back(leg_2_start * leg_u);
    leg_u = leg_d * leg_u;
    leg.vectorModels.push_back(leg_2_start * leg_u);

    //добавляем 4 ножки в нашу модель
    for (int i = 0; i < 4; ++i) {
        for (auto &model:leg.vectorModels)
            vectorModels.push_back(r_90 * model);

        r_90.rotate(90, 0, 1, 0);
    };

//    крышка
    Model up({
                     Point3D(-CH_D - CH_L_b, -CH_L_a, -CH_D - CH_L_b),
                     Point3D(CH_D + CH_L_b, -CH_L_a, -CH_D - CH_L_b),
                     Point3D(CH_D + CH_L_b, -CH_L_a, CH_D + CH_L_b),
                     Point3D(-CH_D - CH_L_b, -CH_L_a, CH_D + CH_L_b)
             }, Qt::red);
    up = leg_d * up;

    vectorModels.push_back(up);
//    матрица для поднятия up и отрисовки верхней части сидушки
    QMatrix4x4 up_up;
    up_up.translate(0, -CH_L_a / 4., 0);

    vectorModels.push_back(up_up * up);

    //    стенка крышки
    Model up_b({
                       Point3D(-CH_D - CH_L_b, CH_L_a, CH_D + CH_L_b),
                       Point3D(CH_D + CH_L_b, CH_L_a, CH_D + CH_L_b),
                       Point3D(CH_D + CH_L_b, CH_L_a - CH_L_a / 4., CH_D + CH_L_b),
                       Point3D(-CH_D - CH_L_b, CH_L_a - CH_L_a / 4., CH_D + CH_L_b)
               }, Qt::blue);
    for (int i = 0; i < 4; ++i) {
        vectorModels.push_back(up_b);
        up_b = r_90*up_b;
    }

}

Tumba::Tumba(double k, double sizeH) :
        Object({}) {
    Model inSquare({Point3D(-LEN_X, -LEN_Y, LEN_Z),
                    Point3D(LEN_X, -LEN_Y, LEN_Z),
                    Point3D(LEN_X, LEN_Y, LEN_Z),
                    Point3D(-LEN_X, LEN_Y, LEN_Z)}, Qt::red);
    Model centerSquare({Point3D(-LEN_X, -sizeH * k, LEN_Z),
                        Point3D(LEN_X, -sizeH * k, LEN_Z),
                        Point3D(LEN_X, sizeH * k, LEN_Z),
                        Point3D(-LEN_X, sizeH * k, LEN_Z)}, Qt::blue);
    QMatrix4x4 rt_y_90, t_up, t_down;
    rt_y_90.rotate(90 * RAD, 0, 1, 0);
    t_up.translate(0, -20 * LEN_Y, 0);
    t_down.translate(0, 20 * LEN_Y, 0);
    for (int i = 0; i < 4; ++i) {
        vectorModels.push_back(centerSquare);
        vectorModels.push_back(t_up * inSquare);
        vectorModels.push_back(t_down * inSquare);
        inSquare = rt_y_90 * inSquare;
        centerSquare = rt_y_90 * centerSquare;
    }

    Model outSquareL({Point3D(-LEN_X - 2, -21 * LEN_Y, LEN_Z),
                      Point3D(-(LEN_X + LEN_Y * 2), -21 * LEN_Y, LEN_Z),
                      Point3D(-(LEN_X + LEN_Y * 2), 21 * LEN_Y, LEN_Z),
                      Point3D(-LEN_X - 2, 21 * LEN_Y, LEN_Z)}, Qt::green);
    QMatrix4x4 t_back, t_rigth;
    t_back.translate(0, 0, -2 * LEN_Z);
    t_rigth.translate(2 * (LEN_X + LEN_Y), 0, 0);
    for (int i = 0; i < 2; ++i) {
        vectorModels.push_back(outSquareL);
        vectorModels.push_back(t_rigth * outSquareL);
        outSquareL = t_back * outSquareL;
    }

    Model outSquareS({Point3D(-LEN_X - 2, 21 * LEN_Y, -LEN_Z),
                      Point3D(-(LEN_X + LEN_Y * 2), 21 * LEN_Y, -LEN_Z),
                      Point3D(-(LEN_X + LEN_Y * 2), 21 * LEN_Y, LEN_Z),
                      Point3D(-LEN_X - 2, 21 * LEN_Y, LEN_Z)}, Qt::black);
    QMatrix4x4 t_up_s;
    t_up_s.translate(0, -42 * LEN_Y, 0);
    for (int i = 0; i < 2; ++i) {
        vectorModels.push_back(outSquareS);
        vectorModels.push_back(t_up_s * outSquareS);
        outSquareS = t_rigth * outSquareS;
    }

}
