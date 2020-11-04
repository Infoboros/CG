//
// Created by ouroboros on 02.10.2020.
//
#include "../Headers/model3d.h"

Model operator*(Matr &matr, Model &model) {
    vector<Point3D> newVec;
    for (auto &vec: model.vectorPoints)
        newVec.emplace_back(matr * vec.point);
    return Model(newVec);
}

void Model::draw(QPainter &painter) {
    size_t size = vectorPoints.size() - 1;
    for (int i = 0; i < size; ++i)
        painter.drawLine(QPointF(vectorPoints[i].x(), vectorPoints[i].y()),
                         QPointF(vectorPoints[i + 1].x(), vectorPoints[i + 1].y()));
    painter.drawLine(QPointF(vectorPoints[size].x(), vectorPoints[size].y()),
                     QPointF(vectorPoints[0].x(), vectorPoints[0].y()));

}

Object operator*(Matr matr, Object &object) {
    vector<Model> newVec;
    for (auto &model: object.vectorModels)
        newVec.push_back(matr * model);
    return Object(newVec);
}

void Object::draw(QPainter &painter) {
    for (auto &model: vectorModels)
        model.draw(painter);
}

void Object::drawFront(QPainter &painter) {
    draw(painter);
}

void Object::drawPorf(QPainter &painter) {
    Matr rt = RotateMY(90 * RAD);
    (rt * (*this)).draw(painter);
}

void Object::drawUp(QPainter &painter) {
    Matr rt = RotateMX(90 * RAD);
    (rt * (*this)).draw(painter);
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

Lampa::Lampa(double k) : Object({}) {
    Matr up = TranslateM(0, U_Y, 0);
    Matr pol = TranslateM(0, U_Y/2., 0);
    Model sixFigure = SixFigure(S_R);

    sixFigure = up * sixFigure;
    vectorModels.push_back(sixFigure);
    vectorModels.push_back(pol*sixFigure);
    //вектор для рамки
    vector<Point3D> vecRamca({{0, U_Y,-S_R},
                              {0, 3 * U_Y/2.,-S_R},
                              {0, 3 * U_Y/2. -10, 0},
                              {0, 3 * U_Y/2., S_R},
                              {0, U_Y, S_R}});
    for (double i = U_Y; i < 61.; i += (61.-U_Y)/(k + 1.)) {
        double radiusSix = getRadiusSix(i);
        Model tmpSixFigure = SixFigure(radiusSix);
        Matr tr = TranslateM(0, i, 0);
        vectorModels.push_back(tr * tmpSixFigure);

        vecRamca.insert(vecRamca.begin(), {0, i, -radiusSix});
        vecRamca.emplace_back(0, i, radiusSix);
    }
    vecRamca.insert(vecRamca.begin(), {0, 62, 0});
    vecRamca.emplace_back(0, 62, 0);
    Model ramca = Model(vecRamca);
    //у нас три рамки
    Matr r_60 = RotateMY(60 * RAD);
    for (int i = 0; i < 3; ++i) {
        vectorModels.push_back(ramca);
        ramca = r_60*ramca;
    }

}

double Lampa::getRadiusSix(double y) {
    if (y < 40.)
        return -y * y / 200. + 44;
    else {
        y -= 22;
        return -y * y / 50 + 42;
    }
}


SixFigure::SixFigure(double radius) : Model({}) {
    Point3D sixPoint(0, 0, radius);
    Matr r_60 = RotateMY(60 * RAD);

    //Создаем 6ти угольник
    for (int i = 0; i < 6; ++i) {
        vectorPoints.push_back(sixPoint);
        sixPoint = r_60 * sixPoint.point;
    }
}
