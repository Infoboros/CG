//
// Created by ouroboros on 19.07.2020.
//
#include "../Headers/line.h"

void line_brezenhem(int x0, int y0, int x1, int y1, HDC hdc, COLORREF cf) {

    int delta_x = abs(x1 - x0);
    int delta_y = abs(y1 - y0);
    int error = 0;
    int delta_err = delta_y + 1;
    int y = 0;
    int dir_y = y1 - y0;

    dir_y = dir_y > 0 ? 1 : -1;

    for (int x = x0; x <= x1; ++x) {
        SetPixel(hdc, x, y, cf);
        error += delta_err;
        if (error >= (delta_x + 1)) {
            y += dir_y;
            error -= delta_x + 1;
        }
    }
}
