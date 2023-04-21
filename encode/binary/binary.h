#ifndef CH_ENCODE_BINARY_H
#define CH_ENCODE_BINARY_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


long byteToInt(uint8_t *b, int byteLen, bool isBigEndian);
uint8_t *intToByte(long v, int byteLen, bool isBigEndian);
uint64_t byte8ToInt(uint8_t *b, int byteLen, bool isBigEndian);
void intTo8Byte(uint64_t v, int byteLen, uint8_t *result, bool isBigEndian);
void byte_copy(uint8_t *out,uint8_t *in,  int len, bool BigEndian) ;
#endif