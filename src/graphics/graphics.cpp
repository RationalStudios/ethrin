#include <graphics/graphics.h>

void __draw_circle(uint32_t* buffer, int xc, int yc, int x, int y, uint32_t color)
{
    draw_pixel(buffer, xc + x, yc + y, color);
    draw_pixel(buffer, xc - x, yc + y, color);
    draw_pixel(buffer, xc + x, yc - y, color);
    draw_pixel(buffer, xc - x, yc - y, color);
    draw_pixel(buffer, xc + y, yc + x, color);
    draw_pixel(buffer, xc - y, yc + x, color);
    draw_pixel(buffer, xc + y, yc - x, color);
    draw_pixel(buffer, xc - y, yc - x, color);
}
void draw_circle(uint32_t* buffer, int x_center, int y_center, int r, uint32_t color)
{
    int x = 0, y = r, d = 3 - (2 * r);
    //Draw an initial circle
    __draw_circle(buffer, x_center, y_center, x, y, color);
    while(y >= x)
    {
        //Add one to x
        x++;
        //Check if the distance > 0
        if(d > 0)
        {
            //Take one from y
            y--;
            //Subtract x from y, multiply result by 4, add d, subtract 10
            d = d + 4 * (x - y) + 10;
        }
        else
            //Multiply x and 4, add d, add 6
            d = d + 4 * x + 6;
        //Draw the circle again
        __draw_circle(buffer, x_center, y_center, x, y, color);
    }
}