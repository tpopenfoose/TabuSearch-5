#ifndef GLOBALNE_H
#define GLOBALNE_H

#include <QVector>
#include <QString>

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

enum FigureName
{
   kolo, kwadrat, trojkat, prostokat
};

struct Figure
{
    int x;
    int y;
    FigureName figureName;
    int pozycja;
};

struct TSF
{
    ConfigData data;
    QVector<Figure> all;

    QVector <Figure> result;
    QVector <Figure> rest;
};

#endif // GLOBALNE_H
