#ifndef PSF_H
#define PSF_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    //Font magic for identification
    uint32_t magic;
    //Version is zero
    uint32_t version;
    //Bitmap offset
    uint32_t header_size;
    //Font flags, 0 if its unicode
    uint32_t flags;
    //Number of glyphs in font
    uint32_t num_glyph;
    //Size of each glyph
    uint32_t bytes_per_glyph;
    //Font height in pixels
    uint32_t height;
    //Font width in pixels
    uint32_t width;
} psf_font;

extern char _binary_assets_font_psf_start;
extern char _binary_assets_font_psf_end;
void put_char(unsigned short int c, int x, int y, uint32_t fg, uint32_t bg);
void write_string(const char* text, int x, int y, uint32_t fg, uint32_t bg);
void init_psf(uint32_t *buffer, int scan_line);
#endif