//
// Created by ouroboros on 13.09.2020.
//

#ifndef LAB1_CURVEDATA_H
#define LAB1_CURVEDATA_H

#include <QtGui/QColor>
#include <QtGui/QPen>
#include <utility>

#include <math.h>

class CurveData {
protected:
    QPen curvenPen;
public:
    explicit CurveData(QPen p):curvenPen(std::move(p)){};

    virtual double F(double) { return 0; }

    QPen getPen(){
        return curvenPen;
    }
};

class SinCurveData : public CurveData {
public:

    SinCurveData(): CurveData(QPen(Qt::red)){};
    double F(double x) override {
        return sin(x);
    }
};

class CosCurveData : public CurveData {
public:

    CosCurveData(): CurveData(QPen(Qt::blue)){};
    double F(double x) override {
        return cos(x);
    }
};

class LineCurveData : public CurveData {
public:

    LineCurveData(): CurveData(QPen(Qt::green)){};
    double F(double x) override {
        return x;
    }
};

class TextCurveData : public CurveData {
private:
    QString text;
public:
    TextCurveData(QString t): CurveData(QPen(QColor(rand()%255, rand()%255, rand()%255))), text(t){

    };
    double F(double x) override{
        ofstream pythonOutput("tmp.py", ios::out);
        pythonOutput << "from math import *" << endl;
        pythonOutput << "with open(\"out.txt\", \"w\") as f:" << endl;
        char buf[80];
        sprintf(buf, "%f", x);
        QString out("   f.write(\"\%10.10f\"\%(");
        for (auto ch: text) {
            if (ch == QChar('x'))
                out += QString(buf).replace(',', '.');
            else
                out += ch;
        }
        out += QString("))");
        pythonOutput << out.toStdString() << endl;
        system("python3 tmp.py");
        ifstream inputPython("out.txt", ios::in);
        double result;
        inputPython >> result;
        pythonOutput.close();
        inputPython.close();
        return result;
    }
};

#endif //LAB1_CURVEDATA_H
