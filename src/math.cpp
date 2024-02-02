#include <math.h>
#include <stdint.h>

uint32_t pow(int num, int power)
{
    uint32_t res = 0;
    if(power == 0)
        return 1;
    for(int i = 0; i < power - 1; i++)
    {
        res += num * num;
    }
    return res;
}

float powf(float num, float power)
{
    float res = 0;
    if(power == 0)
        return 1;
    for(int i = 0; i < power - 1; i++)
    {
        res += num * num;
    }
    return res;
}