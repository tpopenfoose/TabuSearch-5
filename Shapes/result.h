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
    virtual std::vector<std::shared_ptr<Shape>> getResult();
    virtual std::vector<std::shared_ptr<Shape>> getRest();
    virtual std::vector<std::shared_ptr<Shape>> getAll();
    virtual void set_result(std::vector<std::shared_ptr<Shape>> p_result);
    virtual void set_rest(std::vector<std::shared_ptr<Shape>> p_rest);
    virtual void set_all(std::vector<std::shared_ptr<Shape>> p_all);
    virtual void set_data(ConfigData p_data);
    Result & operator =(const Result & result);
    virtual int get_size() const;
    virtual int get_width() const;
    virtual int get_height() const;
    virtual int get_tabusize();
    virtual int get_iteration();
    virtual int get_tabutime();
    virtual int get_procent() const;
private:
    std::vector<std::shared_ptr<Shape>> m_result;
    int m_range;
    ConfigData m_data;
};

#endif // RESULT_H
