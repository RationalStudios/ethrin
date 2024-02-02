#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <vesa/vesa.h>
#include <graphics/colors.h>
void __draw_circle(uint32_t* buffer, int xc, int yc, int x, int y, uint32_t color);
void draw_circle(uint32_t* buffer, int x_center, int y_center, int r, uint32_t color);
#endif