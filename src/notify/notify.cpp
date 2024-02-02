#include <notify/notify.h>
#include <stdarg.h>
#include <stdio/stdio.h>
int curr_x = 1;
int curr_y = 1;

void notify_char(char c)
{
    if(c == '\n')
    {
        curr_y += 18;
        curr_x = 1;
    }
    else
    {
        put_char(c, curr_x, curr_y, WHITE, DEFAULT_BACKGROUND_COLOR);
        curr_x += 8;
    }
}

void notify(char *text, ...)
{
#ifdef DEBUG
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, text);
    for(p = text; *p; p++) {
        if(*p != '%') {
            notify_char(*p);
            continue;
        }
        switch (*++p) {
            case 'c':
            {
                sval = (char*)(va_arg(ap, int) & ~0xFFFFFF00);
                notify_char((int) sval);
                break;
            }
            case 'd':
            {
                ival = va_arg(ap, int);
                notify("%f", ival );
                break;
            }
            case 'f':
            {
                dval  = va_arg(ap, double);
                notify("%f", dval);
                break;
            }
            case 's':
            {
                for(sval = va_arg(ap, char *); *sval; sval++)
                    notify_char(*sval);
                break;
            }
            case 'x':
            {
                //Get next argument
                ival = va_arg(ap, int);
                //Prepare a 32 character long string
                char str[32] = {0};
                //Convert the integer ival to a string
                itoa(ival, 16, str);
                //Write the hex
                write_string(str, curr_x, curr_y, WHITE, DEFAULT_BACKGROUND_COLOR);
                //Update current x by 8 bits
                curr_x += 8;
                break;
            }
            default:
            {
                notify_char(*p);
                break;
            }
        }
    }
    notify_char('\n');
#endif
}