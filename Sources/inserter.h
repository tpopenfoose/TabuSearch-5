#ifndef INSERTER_H
#define INSERTER_H

#include <QVector>
#include "globalne.h"
#include <QObject>
#include <memory>
#include "result.h"

#include <iostream>
using Matrix = std::vector<std::vector<bool>>;
//using Pair=std::pair<int, int>;

class Pair : public std::pair<int, int>
{
    using std::pair<int, int>::pair;
};

class Grid
{
public:
    Grid(int width, int height);
    bool operator==(const Grid& p_grid);
    Matrix & data();

private:
    Matrix m_grid;
};

class Inserter : public QObject
{
    Q_OBJECT
public:
    explicit Inserter(QObject *parent = 0);
    ~Inserter();

    std::unique_ptr<Result> insert(std::unique_ptr<Result> p_result);

private:
    std::unique_ptr<Result> m_result;
    std::vector<std::shared_ptr<Shape>> input;

    //std::unique_ptr<Grid> test_grid1;
    //std::unique_ptr<Grid> test_grid2;
    bool** grid;
    bool** f_grid;

    int m_maximal_y;
    int m_maximal_x;

    int current_line;
    int current_column;
    unsigned int counter;
    bool counter_back;
    bool insert_stop;
    bool new_line;
    int column_count;
    int line_count;

    void init_grid(void);
    void grid_clear(bool);

    bool shapes_overlines(void);

    Pair calculate_position(std::shared_ptr<Shape> s);
    void calculate_new_f_grid(std::shared_ptr<Shape> s, Pair p_coordinates);
    void delete_grids();
    Pair fit_non_overlaping_shape_on_x_and_y(std::shared_ptr<Shape> s, Pair p_coordinates);
    Pair fit_non_overlaping_shape_on_y(std::shared_ptr<Shape> s, Pair p_coordinates);
    Pair fit_non_overlaping_shape_on_x(std::shared_ptr<Shape> s, Pair p_coordinates);
    Pair fit_non_overlaping_shape(std::shared_ptr<Shape> s, Pair p_coordinates);
    Pair fit_overlaping_shape(std::shared_ptr<Shape> s, Pair p_coordinates);
    Pair fit_overlaping_shape_on_x_and_y(std::shared_ptr<Shape> s, Pair p_coordinates);
    Pair fit_overlaping_shape_on_y(std::shared_ptr<Shape> s, Pair p_coordinates);
    Pair fit_overlaping_shape_on_x(std::shared_ptr<Shape> s, Pair p_coordinates);

    void init_insert(void);
};
#endif // INSERTER_H
