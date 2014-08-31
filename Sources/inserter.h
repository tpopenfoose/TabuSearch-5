#ifndef INSERTER_H
#define INSERTER_H

#include <QVector>
#include <QObject>
#include <memory>
#include <result.h>
#include <IGrid.h>

#include <iostream>

class Pair : public std::pair<int, int>
{
    using std::pair<int, int>::pair;
};

typedef std::pair<std::vector<std::shared_ptr<Shape>>, int> Shapes;

class Inserter : public QObject
{
    Q_OBJECT
public:
    explicit Inserter(QObject *parent = 0);
    ~Inserter();

    Shapes insert(std::vector<std::shared_ptr<Shape>> p_shapes, const ConfigData &p_data);

protected:
    std::unique_ptr<IGrid> grid;
    std::unique_ptr<IGrid> f_grid;
private:
    ConfigData m_data;
    std::vector<std::shared_ptr<Shape>> input;

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
