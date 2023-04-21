#ifndef INC_HEX_H_
#define INC_HEX_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef union {
  uint32_t value;
  struct {
    unsigned mantissa : 23;
    unsigned exponent : 8;
    unsigned sign : 1;
  };
} IEEEFLOAT_T;

float hexToIEEEFloat(uint32_t value);

uint8_t FromHexChar(uint8_t *c);
uint8_t HexStringToDecString(uint8_t *dst, uint8_t *src, int len);

uint8_t DecToBCD(uint8_t v);
uint8_t BCDToDec(uint8_t v);
uint8_t HEXBCDToDec(uint8_t v);

// 两个字节的数，小端，自增
void u8Increase(uint8_t v[2]);

#endif