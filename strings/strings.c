#include "strings.h"

int lastIndex(char *data, char sep, int len)
{
    int i = 0;
    for (i = len; i >= 0; i--)
    {
        if (data[i] == sep)
        {
            return i;
        }
    }
    return -1;
}

int indexAny(char *data, char sep, int num, int len)
{
    int i = 0;
    int count = 0;
    for (i = len; i >= 0; i--)
    {
        if (data[i] == sep)
        {
            count++;
            if (count == num)
            {
                return i;
            }
        }
    }
    return -1;
}