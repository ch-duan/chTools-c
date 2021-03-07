#ifndef CH_ENCODE_BINARY_H
#define CH_ENCODE_BINARY_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

long byteToInt(uint8_t *b, int byteLen, bool isBigEndian);
uint8_t *intToByte(long v, int byteLen, bool isBigEndian);
#endif