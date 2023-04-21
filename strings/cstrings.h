#ifndef CH_STRING_H
#define CH_STRING_H
#include <stdint.h>

int lastIndex(char *data, char sep, int len);
int indexAny(char *data, char sep, int num, int len);

int hexstringtobyte(char *in, unsigned char *out, int len);

#endif