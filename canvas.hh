#pragma once

#include <iostream>
#include <vector>

#include <cstring>
#include <cstdlib>

using std::size_t, std::vector;




typedef vector<vector<bool>> grid_t;

class Canvas {
public:
    const int m_width, m_height;
    grid_t m_grid;

    Canvas(int width, int height);

    void update(void);

private:
protected:
};
