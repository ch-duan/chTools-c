#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc.h"
#include "encode/binary/binary.h"
#include "strings/cstrings.h"
#include "strings/hex.h"
typedef struct {
  uint8_t Frameheader[3];
  uint8_t Protocol[4];
  uint8_t Len[2];  // 消息帧不算data为14
  uint8_t TaskID[2];
  uint8_t Cmd;
  // uint8_t *data;
  uint16_t Crc16;
} IAP_DATA2;

void byte_copy_test() {
  uint8_t ss[] = {0x01, 0x02, 0x03, 0x04};
  uint8_t sd[4];
  byte_copy(sd, ss, 4, true);
  for (int i = 0; i < 4; i++) {
    printf("%d ", sd[i]);
  }
  printf("\r\n");

  byte_copy(sd, ss, 4, false);
  for (int i = 0; i < 4; i++) {
    printf("%d ", sd[i]);
  }
  printf("\r\n");
}

/**
 * 比较版本号
 *
 * @param v1 第一个版本号
 * @param v2 第二个版本号
 *
 * @return 如果版本号相等，返回 0,
 *         如果第一个版本号低于第二个，返回 -1，否则返回 1.
 */
int compareVersion(const char *v1, const char *v2) {
  // printf("%d\r\n",v1);
  // printf("%d\r\n",v2);

  const char *p_v1 = v1;
  const char *p_v2 = v2;

  while (*p_v1 && *p_v2) {
    char buf_v1[32] = {0};
    char buf_v2[32] = {0};

    char *i_v1 = strchr(p_v1, '.');
    char *i_v2 = strchr(p_v2, '.');

    if (!i_v1 || !i_v2)
      break;

    if (i_v1 != p_v1) {
      strncpy_s(buf_v1, p_v1, i_v1 - p_v1);
      p_v1 = i_v1;
    } else
      p_v1++;

    if (i_v2 != p_v2) {
      strncpy_s(buf_v2, p_v2, i_v2 - p_v2);
      p_v2 = i_v2;
    } else
      p_v2++;

    int order = atoi(buf_v1) - atoi(buf_v2);
    if (order != 0)
      return order < 0 ? -1 : 1;
  }

  double res = atof(p_v1) - atof(p_v2);
  printf("%s,%s,%s,%s\r\n", v1, p_v1, v2, p_v2);
  if (res < 0)
    return -1;
  if (res > 0)
    return 1;
  return 0;
}

int main() {
  //   unsigned char buf[4] = {0xd2, 0x02, 0x96, 0x49};
  //   unsigned char *buf2 = (unsigned char *) malloc(4);
  //   long a = 0;
  //   // unsigned char *buf2 = {0x56, 0x00, 0x11, 0x00};
  //   printf("%llu,%d\r\n", strlen(buf), sizeof(buf) / sizeof(unsigned char));
  //   a = byteToInt(buf, 4, false);
  //   printf("%ld\r\n", a);
  //   buf2 = intToByte(a, 4, false);
  //   printf("%ld\r\n", byteToInt(buf2, 4, false));

  // char *ptr;
  // unsigned char appstatus=0;
  // unsigned char tmp[100]="1,DA05C23E9F39F6F89AEDF56D86DB0A88";
  // unsigned char md5[16]={0};
  // if (strstr((char *) tmp, ",") != NULL) {
  //   appstatus = strtoul((char *) tmp, &ptr, 10);
  // }

  // char *md5_s = strstr((const char *) tmp, ",") + 1;
  // if (strlen(md5_s) < 16) {
  //   return -1;
  // }
  // hexstringtobyte((char *) md5_s, md5, 32);
  // printf("app md5:");
  // for (int i = 0; i < 16; i++) {
  //   printf("%02X", md5[i]);
  // }
  // printf("\r\n");
  printf("%d\r\n", compareVersion("2.2.1", "2.2.0"));
  printf("%d\r\n", compareVersion("2.2.1", "2.1.9"));
  printf("%d\r\n", compareVersion("2.2.1", "2.2.01"));
  printf("%d\r\n", compareVersion("2.2.1", "2.2.1"));
  printf("%d\r\n", compareVersion("2.2", "2.1.1"));
  printf("%d\r\n", compareVersion("2.2", "2.2.1"));
  printf("%d\r\n", compareVersion("2.2.3.1", "2.2.3.5"));
  printf("%d\r\n", compareVersion("2.2.3.1", "2.2.3.0"));
  printf("%d\r\n", compareVersion("2.2", "2.2.1.4.5"));
  printf("%d\r\n", compareVersion("2.2.3.4", "2.2.4.4.5"));
  printf("%d\r\n", compareVersion("2.2.3.4.5.6", "2.2.3.4.5.12"));
  printf("%d\r\n", compareVersion("2.2.3.4.5.6", "2.2.2.4.5.12"));
  printf("%d\r\n", compareVersion("3.0.0.1", "3.0.0.0.1"));
  printf("%d\r\n", compareVersion("3.1", "3.1."));

  printf("test pass.");

fail:
  printf("this is a test\r\n");

  // IAP_DATA2 iAP_DATA2 = {
  //     .Frameheader = {0x49, 0x41, 0x50},
  //     .Protocol = {0x01, 0x00, 0x00, 0x00},
  //     .Len = {0x28, 0x00},
  //     .TaskID = {0x0, 0x0},
  //     .Cmd = 1,
  //     .Crc16 = 0,
  // };
  // char m_md5[9] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
  // int len = 14 + 10;
  // iAP_DATA2.Len[0] = len & 0xff;
  // iAP_DATA2.Len[1] = len >> 8;
  // uint8_t *p = (uint8_t *) malloc(len);
  // p[12] = 1;
  // memcpy(p + 13, m_md5, 9);
  // iAP_DATA2.Crc16 = CRC16(p, len - 2);
  // p[len - 2] = iAP_DATA2.Crc16 & 0xff;
  // p[len - 1] = iAP_DATA2.Crc16 >> 8;
  // uint8_t *c = (uint8_t *) &iAP_DATA2.Crc16;
  // byte_copy_test();
  uint8_t a[4] = {0x20, 0x34, 0x90, 0xBF};
  printf("%f\r\n", hexToIEEEFloat(0XBF90B5C6));
  return 0;
}