//
// Created by ouroboros on 02.10.2020.
//
#include "../Headers/model3d.h"

Model operator*(QMatrix4x4 &matr, Model &model) {
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

Object operator*(QMatrix4x4 matr, Object &object) {
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
    QMatrix4x4 rt;
    rt.rotate(90*RAD, 0, 1, 0);
    (rt*(*this)).draw(painter);
}

void Object::drawUp(QPainter &painter) {
    QMatrix4x4 rt;
    rt.rotate(90*RAD, 1, 0, 0);
    (rt*(*this)).draw(painter);
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
