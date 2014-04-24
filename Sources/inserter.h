#ifndef INSERTER_H
#define INSERTER_H

#include <QVector>
#include "globalne.h"
#include <QObject>

class Inserter : public QObject
{
    Q_OBJECT
public:
    explicit Inserter(QObject *parent = 0);
    ~Inserter();

    TSF insert(TSF);
private:
    ConfigData data;

    QVector<Figure> input;
    QVector<Figure> output;

    bool** grid;
    bool** f_grid;

    int pozycja_x;
    int pozycja_y;

    int current_line;
    int current_column;
    int counter;
    bool counter_back;
    bool insert_stop;
    bool new_line;
    int column_count;
    int line_count;

    void init_grid(void);
    void fill_grid(Figure);
    void grid_clear(bool);
    void fill_f_grid(Figure);

    void fill_square(Figure,bool);
    void fill_elipse(Figure,bool);
    void fill_rectangle(Figure,bool);
    void fill_triangle(Figure,bool);

    double prosta1(Figure,int);
    double prosta2(Figure,int);

    bool compare_grids(void);

    void calculate_position(Figure);
    void calculate_new_f_grid(Figure);

    void init_insert(void);
    void insert_end(void);
};
#endif // INSERTER_H
