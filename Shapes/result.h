#ifndef RESULT_H
#define RESULT_H
#include "shape.h"
#include "globalne.h"
#include <memory>

class Result
{
public:
    Result();
    Result(const Result & result);
    std::vector<std::shared_ptr<Shape>> getResult();
    std::vector<std::shared_ptr<Shape>> getRest();
    std::vector<std::shared_ptr<Shape>> getAll();
    void set_result(std::vector<std::shared_ptr<Shape>> p_result);
    void set_rest(std::vector<std::shared_ptr<Shape>> p_rest);
    void set_all(std::vector<std::shared_ptr<Shape>> p_all);
    void set_data(ConfigData p_data);
    Result & operator =(const Result & result);
    int get_size() const;
    int get_width() const;
    int get_height() const;
    int get_tabusize();
    int get_iteration();
    int get_tabutime();
    int get_procent() const;
private:
    std::vector<std::shared_ptr<Shape>> m_result;
    int m_range;
    ConfigData m_data;
};

#endif // RESULT_H
