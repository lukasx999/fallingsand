#include <iostream>
#include <cstdio>
#include <format>

namespace rl {
#include <raylib.h>
}

#include "canvas.hh"


#define WIDTH 1920
#define HEIGHT 1080
#define X_OFFSET (float) WIDTH/4
#define Y_OFFSET 50
#define BG rl::BLACK
#define RECT_SIZE 20
#define RECT_COLOR rl::BLUE



static void
draw_canvas_borders(Canvas &c) {

    // TOP
    rl::DrawLine(X_OFFSET,
             Y_OFFSET,
             c.m_width * RECT_SIZE + X_OFFSET,
             Y_OFFSET, rl::RED);

    // BOT
    rl::DrawLine(X_OFFSET,
             c.m_height * RECT_SIZE + Y_OFFSET,
             c.m_width  * RECT_SIZE + X_OFFSET,
             c.m_height * RECT_SIZE + Y_OFFSET,
             rl::RED);

    // LEFT
    rl::DrawLine(X_OFFSET,
             Y_OFFSET,
             X_OFFSET,
             c.m_height * RECT_SIZE + Y_OFFSET,
             rl::RED);

    // RIGHT
    rl::DrawLine(X_OFFSET + c.m_width * RECT_SIZE,
             Y_OFFSET,
             X_OFFSET + c.m_width * RECT_SIZE,
             c.m_height*RECT_SIZE + Y_OFFSET,
             rl::RED);

}





static void spawn_cell(Canvas &c) {
    c.m_grid[c.m_width/2][0] = 1;
}


static void normalize_cursor(Canvas &c, rl::Vector2 &pos) {

    pos.x -= X_OFFSET;
    pos.y -= Y_OFFSET;
    pos.x /= RECT_SIZE * c.m_width;
    pos.y /= RECT_SIZE * c.m_height;
    pos.x *= c.m_width;
    pos.y *= c.m_height;
    pos.x = static_cast<int>(pos.x);
    pos.y = static_cast<int>(pos.y);

}




int main(void) {


    Canvas canvas(50, 50);


    for (vector<bool> row : canvas.m_grid) {
        for (bool col : row) {
            std::cout << col;
        }
        std::cout << std::endl;
    }


    srand(time(NULL));


    rl::SetTraceLogLevel(rl::LOG_ERROR); 
    rl::SetTargetFPS(60);
    rl::InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");

    while (!rl::WindowShouldClose()) {
        rl::BeginDrawing();
        {
            rl::ClearBackground(BG);

            // rendering
            for (int x = 0; x < canvas.m_width; ++x) {
                for (int y = 0; y < canvas.m_height; ++y) {

                    if (canvas.m_grid[x][y])
                        DrawRectangle(x * RECT_SIZE + X_OFFSET, y * RECT_SIZE + Y_OFFSET, RECT_SIZE, RECT_SIZE, RECT_COLOR);

                }
            }

            // logic
            canvas.update();
            draw_canvas_borders(canvas);


            if (rl::IsKeyDown(rl::KEY_SPACE)) {
                spawn_cell(canvas);
            }


            rl::Vector2 pos = rl::GetMousePosition();
            if (rl::IsMouseButtonDown(rl::MOUSE_BUTTON_LEFT)) {
                normalize_cursor(canvas, pos);
                canvas.m_grid[pos.x][pos.y] = 1;
            }





        }
        rl::EndDrawing();
    }
    rl::CloseWindow();
    return EXIT_SUCCESS;
}
