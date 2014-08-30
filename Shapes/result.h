#ifndef RESULT_H
#define RESULT_H
#include "shape.h"
#include <memory>
#include "config_data.h"

class Result
{
public:
    Result() = default;
    Result(const Result & result);
    Result & operator =(const Result & result);

    virtual int waste(const ConfigData &p_data) const;
    virtual std::vector<std::shared_ptr<Shape>> getResult() const;
    virtual std::vector<std::shared_ptr<Shape>> getRest() const;
    virtual std::vector<std::shared_ptr<Shape>> getAll() const;
    virtual void set_result(std::vector<std::shared_ptr<Shape>> p_result, int p_range);

private:
    std::vector<std::shared_ptr<Shape>> m_result;
    int m_range;
};

#endif // RESULT_H
