#include <vesa/vesa.h>

struct vesa_mode_info vesa_mode[1];

void draw_pixel(uint32_t *framebuffer, int x, int y, uint32_t color)
{
    unsigned index = y * vesa_mode[0].height + x;
    framebuffer[index] = color;
    framebuffer[index + 1] = color;
    framebuffer[index + 2] = color;
}


void init_vesa(unsigned int* multiboot_header)
{
    //Set initial vesa mode's buffer
    vesa_mode[0].framebuffer = (uint32_t*) multiboot_header[22];
    //Set the pitch
    vesa_mode[0].pitch = multiboot_header[23];
    //Set the width
    vesa_mode[0].width = multiboot_header[24];
    //Set the height
    vesa_mode[0].height = multiboot_header[25];
    //Set the bpp
    vesa_mode[0].bpp = multiboot_header[26];
    //Now loop and paint red
    for(int x = 0; x < vesa_mode[0].width; x++)
    {
        for(int y = 0; y < vesa_mode[0].height; y++)
        {
            //Draw a pixel
            draw_pixel(vesa_mode[0].framebuffer, x, y, 0x43b7dc);
        }
    }
    int scan_line = vesa_mode[0].width;
    //Initialize PC Screen Font
    init_psf(vesa_mode[0].framebuffer, scan_line);
}
