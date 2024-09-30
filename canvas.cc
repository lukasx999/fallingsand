#include "canvas.hh"


static void fill_grid(grid_t &grid, int width, int height) {

    for (int i=0; i<width; ++i) {
        vector<bool> col;
        grid.push_back(col);

        for (int j=0; j<height; ++j)
            grid[i].push_back(0);

    }

}



Canvas::Canvas(int width, int height)
    : m_width (width)
    , m_height(height)
{

    fill_grid(m_grid, m_width, m_height);

}



void Canvas::update(void) {


    for (    int x = m_width-1;  x >= 0; --x) {
        for (int y = m_height-1; y >= 0; --y) {

            if (m_grid[x][y]) {

                if (y == m_height-1) { // ground collision
                    m_grid[x][y] = 1;
                    continue;
                }

                if (x == m_width-1) { // right wall collision
                    m_grid[x][y] = 1;
                    continue;
                }

                if (x == 0) { // left wall collision
                    m_grid[x][y] = 1;
                    continue;
                }



                if (!m_grid[x][y+1]) { // check below
                    m_grid[x][y] = 0;
                    m_grid[x][y+1] = 1;
                    continue;
                }


                if (!m_grid[x-1][y] && !m_grid[x-1][y+1]) { // check left and diagonal
                    m_grid[x-1][y] = 1;
                    continue;
                }

                if (!m_grid[x+1][y] && !m_grid[x+1][y+1]) { // check right and diagonal
                    m_grid[x+1][y] = 1;
                    continue;
                }



                m_grid[x][y] = 1; // else

            }

        }
    }

}
