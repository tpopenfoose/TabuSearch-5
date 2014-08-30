#include "result.h"
#include <iostream>

Result::Result(const Result & result)
{
    m_range = result.m_range;
    m_result = result.m_result;
}

Result & Result::operator =(const Result & result)
{
    m_range = result.m_range;
    m_result = result.m_result;

    return *this;
}

int Result::waste(const ConfigData& p_data) const
{
   int all = p_data.height * p_data.width;

   int sum = 0;

   for(auto & iter : getResult())
       sum += iter->get_area(p_data.size);

   float p = (float)(all-sum)/all;

   return 100*p;
}

std::vector<std::shared_ptr<Shape>> Result::getResult() const
{
    std::vector<std::shared_ptr<Shape>> temp(m_range);
    std::copy(m_result.begin(),m_result.begin() + m_range, temp.begin());
    return temp;
}

std::vector<std::shared_ptr<Shape>> Result::getRest() const
{
    std::vector<std::shared_ptr<Shape>> temp(m_result.size()-m_range);
    std::copy(m_result.begin() + m_range,m_result.end(), temp.begin());
    return temp;
}

std::vector<std::shared_ptr<Shape>> Result::getAll() const
{
    return m_result;
}

void Result::set_result(std::vector<std::shared_ptr<Shape>> p_result, int p_range)
{
    m_result = p_result;
    m_range = p_range;
}
