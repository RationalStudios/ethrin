#include <stdio/stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <fonts/psf.h>
#include <graphics/colors.h>
#include <notify/notify.h>

struct stdio_buffer *buffer = (struct stdio_buffer *) malloc(sizeof(struct stdio_buffer));
int count;
void add_to_buffer(void *item)
{
    struct stdio_buffer *tmp = (struct stdio_buffer *) malloc(sizeof(struct stdio_buffer));
    tmp->content = item;
    tmp->pos = count;
    tmp->next = NULL;
    tmp->prev = buffer;
    buffer->next = tmp;
    buffer = tmp;
    count++;
}


char buff[32];
//All possible hex characters
char chars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
//Convert hex to string
void htoc(uint16_t hex)
{
    add_to_buffer(&chars[(hex & 0xF0) >> 4]);
    add_to_buffer(&chars[(hex & 0x0F) >> 0]);
}

int8_t is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int8_t is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int8_t is_alpha_num(char c)
{
    return is_digit(c) || is_alpha(c);
}

void itoa(unsigned i, unsigned base, char *buffer)
{
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buff[0] = '0';
		buff[1] = '\0';
		return;
	}

	while (i != 0) {
		buff[pos] = chars[i % base];
		pos++;
		i /= base;
	}
	top=pos--;
	for (opos=0; opos<top; pos--,opos++)
		buff[opos] = buff[pos];
	buff[opos] = 0;
}

int32_t atoi(const char *text)
{
	uint8_t len = (uint8_t) strlen(text);
	int32_t result = 0;
	uint32_t mul = 1;

	while (len > 0 && is_digit(text[len - 1])) //loop from right to left
	{
		result += (text[--len] - '0') * mul;
		mul *= 10;
	}

	if (len == 1 && text[0] == '-') //negative number
	{
		result *= -1;
        len = 0; //completed
	}

    if (len == 0)
    {
        return result; //valid number
    }
	
    return -1; //invalid string
}

void printf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for(p = fmt; *p; p++) {
        if(*p != '%') {
            add_to_buffer(p);
            continue;
        }
        switch (*++p) {
            case 'c':
            {
                sval = (char*)(va_arg(ap, int) & ~0xFFFFFF00);
                add_to_buffer(sval);
                break;
            }
            case 'd':
            {
                ival = va_arg(ap, int);
                printf("%f", ival );
                break;
            }
            case 'f':
            {
                dval  = va_arg(ap, double);
                printf("%f", dval);
                break;
            }
            case 's':
            {
                for(sval = va_arg(ap, char *); *sval; sval++)
                    add_to_buffer(sval);
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
                //Write the integer to the screen
                add_to_buffer(str);
                break;
            }
            default:
            {
                add_to_buffer(p);
                break;
            }
        }
    }
}