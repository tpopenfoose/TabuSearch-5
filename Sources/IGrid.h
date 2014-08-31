#pragma once
#include <vector>

typedef std::vector<std::vector<int>> Matrix;

class IGrid
{
public:
    virtual void create(int p_width, int p_height) = 0;
    virtual void deleteAll() = 0;
    virtual void clear() = 0;
    virtual Matrix& getGrid() = 0;
    virtual bool at(int i, int j) = 0;
};
