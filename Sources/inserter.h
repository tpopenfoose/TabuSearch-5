#ifndef INSERTER_H
#define INSERTER_H

#include <QVector>
#include "globalne.h"
#include <QObject>
#include <memory>

class Inserter : public QObject
{
    Q_OBJECT
public:
    explicit Inserter(QObject *parent = 0);
    ~Inserter();

    TSF insert(TSF);
private:
    ConfigData data;
    std::vector<std::shared_ptr<Shape>> input;
    std::vector<std::shared_ptr<Shape>> output;

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
    void grid_clear(bool);

    bool compare_grids(void);

    void calculate_position(std::shared_ptr<Shape> s);
    void calculate_new_f_grid(std::shared_ptr<Shape> s);

    void init_insert(void);
    void insert_end(void);
};
#endif // INSERTER_H
