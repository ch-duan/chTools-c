#include "binary.h"

#include <stdlib.h>

long byteToInt(uint8_t *b, int byteLen, bool isBigEndian) {
  long result = 0;
  int i = 0;
  if (isBigEndian) {
    for (i = byteLen - 1; i >= 0; i--) {
      result += (long) b[i] << (byteLen - 1 - i) * 8;
    }
  } else {
    for (i = 0; i < byteLen; i++) {
      result += (long) b[i] << i * 8;
    }
  }
  return result;
}

uint8_t *intToByte(long v, int byteLen, bool isBigEndian) {
  uint8_t *b = (uint8_t *) malloc(byteLen);
  int i = 0;
  if (isBigEndian) {
    for (i = byteLen - 1; i >= 0; i--) {
      b[i] = (uint8_t) (v >> (byteLen - 1 - i) * 8);
    }
  } else {
    for (i = 0; i < byteLen; i++) {
      b[i] = (uint8_t) (v >> i * 8);
    }
  }
  return b;
}

uint64_t byte8ToInt(uint8_t *b, int byteLen, bool isBigEndian) {
  uint64_t result = 0;
  int i = 0;
  if (isBigEndian) {
    for (i = byteLen - 1; i >= 0; i--) {
      result += (uint64_t) b[i] << (byteLen - 1 - i) * 8;
    }
  } else {
    for (i = 0; i < byteLen; i++) {
      result += (uint64_t) b[i] << i * 8;
    }
  }
  return result;
}

void intTo8Byte(uint64_t v, int byteLen, uint8_t *result, bool isBigEndian) {
  int i = 0;
  if (isBigEndian) {
    for (i = byteLen - 1; i >= 0; i--) {
      result[i] = (uint8_t) (v >> (byteLen - 1 - i) * 8);
    }
  } else {
    for (i = 0; i < byteLen; i++) {
      result[i] = (uint8_t) (v >> i * 8);
    }
  }
}

void byte_copy(uint8_t *out,uint8_t *in,  int len, bool BigEndian) {
  if (BigEndian) {
    while (len--) {
      *out++ = *(in + len);
    }
  } else {
    while (len--) {
      *out++ = *in++;
    }
  }
}