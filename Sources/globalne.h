#ifndef GLOBALNE_H
#define GLOBALNE_H

#include <QVector>
#include <QString>
#include "shape.h"
#include <memory>

class Point
{
public:

    Point(){}
    Point(int xx,int yy){x=xx;y=yy;}

    float x;
    float y;
};

struct ConfigData
{
    int width;
    int height;
    int size;
    int procent;
    int iteration;
    int tabusize;
    int tabutime;
};

struct TSF
{
    ConfigData data;
    std::vector<std::shared_ptr<Shape>> all;

    std::vector<std::shared_ptr<Shape>> result;
    std::vector<std::shared_ptr<Shape>> rest;
};

#endif // GLOBALNE_H
