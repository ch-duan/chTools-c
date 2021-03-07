#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "encode/binary/binary.h"
#include "strings/strings.h"

int main()
{

    unsigned char buf[4] = {0xd2, 0x02, 0x96, 0x49};
    unsigned char *buf2 = (unsigned char *)malloc(4);
    long a = 0;
    // unsigned char *buf2 = {0x56, 0x00, 0x11, 0x00};
    printf("%d,%d\r\n", strlen(buf), sizeof(buf) / sizeof(unsigned char));
    a = byteToInt(buf, 4, false);
    printf("%ld\r\n", a);
    buf2 = intToByte(a, 4, false);
    printf("%ld\r\n", byteToInt(buf2, 4, false));
    return 0;
}