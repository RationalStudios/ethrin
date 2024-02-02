#include <string.h>

//Compares str1 and str2
int strcmp(const char *str1, const char *str2)
{
    //Convert str1 to unsigned char*
    const unsigned char *ustr1 = (const unsigned char *) str1;
    //The same with str2
    const unsigned char *ustr2 = (const unsigned char *) str2;
    //Characters to be treated as numbers
    unsigned char c1, c2;
    //Loop while c1 and c2 are the same
    do
    {
        //Set c1 to the result of adding 1 to ustr1
        c1 = (unsigned char) *ustr1++;
        //Set c2 to the result of adding 1 to ustr2
        c2 = (unsigned char) *ustr2++;
        //Check if c1 is terminator
        if(c1 == '\0')
            //Subtract c2 from c1
            return c1 - c2;
    } while (c1 == c2);
    //Subtract c1 from c2;
    return c1 - c2;
}

//Gets the amount of values in string str
size_t strlen(const char* str)
{
    //Index to be used for finding length of string
    size_t idx = 0;
    //Loop until str character at idx is terminator
    while(str[idx] != '\0')
        //Update index idx by 1
        idx++;
    //Return the index
    return idx;
}