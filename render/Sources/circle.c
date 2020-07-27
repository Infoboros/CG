//
// Created by ouroboros on 22.07.2020.
//
#include "../Headers/circle.h"

void circle_brezenhem(int R, int x1, int y1, HDC hdc, COLORREF cf) {
    int x = 0;
    int y = R;
    int delta = 1 - 2 * R;
    int error = 0;

    while (y >= 0) {
        SetPixel(hdc, x1 + x, y1 + y, cf);
        SetPixel(hdc, x1 + x, y1 - y, cf);
        SetPixel(hdc, x1 - x, y1 + y, cf);
        SetPixel(hdc, x1 - x, y1 - y, cf);

        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * ++x + 1;
            continue;
        }

        if ((delta > 0) && (error > 0)) {
            delta -= 2 * --y + 1;
            continue;
        }

        delta += 2 * (++x - --y);
    }
}
