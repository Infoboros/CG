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

    return {x / size, y / size, z/size};
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
        (proec*model).draw(painter);
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
