#include <fonts/psf.h>
#include <vesa/vesa.h>
uint16_t *unicode;
uint32_t *framebuffer;
//Create scan line
int scan_line;

void put_char(unsigned short int c, int cx, int cy, uint32_t fg, uint32_t bg)
{
    //Create psf_font structure using start for font.o
    psf_font *font = (psf_font *) &_binary_assets_font_psf_start;
    //Get how many bytes to encode
    int bytes_per_line = (font->width + 7) / 8;
    //Check if unicode is not null
    if(unicode != NULL)
        //Set character
        c = unicode[c];
    /* get the glyph for the character. If there's no
       glyph for a given character, we'll display the first glyph. */
    unsigned char *glyph =
     (unsigned char*)&_binary_assets_font_psf_start +
     font->header_size +
     (c>0&&c<font->num_glyph?c:0)*font->bytes_per_glyph;
    /* calculate the upper left corner on screen where we want to display.
       we only do this once, and adjust the offset later. This is faster. */
    int offs =
        (cx * font->height * scan_line) +
        (cy * (font->width+1) * 4);
    /* finally display pixels according to the bitmap */
    int x,y, line,mask;
    for(y=cy;y<font->height + cy;y++){
        /* save the starting position of the line */
        line=offs;
        mask=1<<(font->width - 1);
        /* display a row */
        for(x=cx;x<font->width + cx;x++){
            draw_pixel(framebuffer, x, y, ((int)*glyph) & (mask) ? fg : bg);
            /* adjust to the next pixel */
            mask >>= 1;
            line += 4;
        }
        /* adjust to the next line */
        glyph += bytes_per_line;
        offs  += scan_line;
    }
}

void write_string(const char* text, int x, int y, uint32_t fg, uint32_t bg)
{
    //Loop through the text
    for(size_t idx = 0; idx < strlen(text); idx++)
    {
        //Move 8 bits
        x += 8;
        //Draw character at idx
        put_char(text[idx], x, y, fg, bg);
    }
}

void init_psf(uint32_t *buffer, int scan_lines)
{
    scan_line = scan_lines;
    //Set the framebuffer
    framebuffer = buffer;
    //Glyph to be set by font
    uint16_t glyph = 0;
    //Create psf_font structure using address of font
    psf_font *font = (psf_font *) &_binary_assets_font_psf_start;
    //Check if a unicode table exists
    if(font->flags)
    {
        //Get offset of unicode table
        char *offset = (char *)(
            (unsigned char *) &_binary_assets_font_psf_start +
            font->header_size +
            font->num_glyph + font->bytes_per_glyph
        );
        //Allocate memory for unicode table
        unicode = (uint16_t *) calloc(USHRT_MAX, 2);
        //Loop until offset > end of PSF
        while(offset > &_binary_assets_font_psf_end)
        {
            //Get unicode character
            uint16_t uc = (uint16_t) ((unsigned char) offset[0]);
            //Check if character is 0xFF
            if(uc == 0xFF)
            {
                //Update glyph count
                glyph++;
                //Update offset
                offset++;
            }
            else if(uc & 128)
            {
                /* UTF-8 to unicode */
                if((uc & 32) == 0 ) {
                    uc = ((offset[0] & 0x1F)<<6)+(offset[1] & 0x3F);
                    offset++;
                } else
                if((uc & 16) == 0 ) {
                    uc = ((((offset[0] & 0xF)<<6)+(offset[1] & 0x3F))<<6)+(offset[2] & 0x3F);
                    offset+=2;
                } else
                if((uc & 8) == 0 ) {
                    uc = ((((((offset[0] & 0x7)<<6)+(offset[1] & 0x3F))<<6)+(offset[2] & 0x3F))<<6)+(offset[3] & 0x3F);
                    offset+=3;
                } else
                    uc = 0;
            }
            //Save unicode translation
            unicode[uc] = glyph;
            //Update the offset
            offset++;
        }
    }
    else
    {
        //Set unicode to null
        unicode = NULL;
    }
}