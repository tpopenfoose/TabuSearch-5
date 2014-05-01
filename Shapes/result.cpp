#include "result.h"
#include <iostream>
Result::Result()
{

}

Result::Result(const Result & result)
{
    m_data = result.m_data;
    m_range = result.m_range;
    m_result = result.m_result;
}

Result & Result::operator =(const Result & result)
{
    m_data = result.m_data;
    m_range = result.m_range;
    m_result = result.m_result;

    return *this;
}

std::vector<std::shared_ptr<Shape> > Result::getResult()
{
    std::vector<std::shared_ptr<Shape>> temp(m_range);
    std::copy(m_result.begin(),m_result.begin() + m_range, temp.begin());
    return temp;
}

std::vector<std::shared_ptr<Shape> > Result::getRest()
{
    std::vector<std::shared_ptr<Shape>> temp(m_result.size()-m_range);
    std::copy(m_result.begin() + m_range,m_result.end(), temp.begin());
    return temp;
}

std::vector<std::shared_ptr<Shape> > Result::getAll()
{
    return m_result;
}

void Result::set_data(ConfigData p_data)
{
    m_data = p_data;
}

void Result::set_result(std::vector<std::shared_ptr<Shape>> p_result, int p_range)
{
    m_result = p_result;
    m_range = p_range;
}

int Result::get_size() const
{
    return m_data.size;
}

int Result::get_width() const
{
    return m_data.width;
}

int Result::get_height() const
{
    return m_data.height;
}

int Result::get_tabusize()
{
    return m_data.tabusize;
}

int Result::get_iteration()
{
    return m_data.iteration;
}

int Result::get_tabutime()
{
    return m_data.tabutime;
}

int Result::get_procent() const
{
    return m_data.procent;
}
