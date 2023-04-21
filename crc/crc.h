#ifndef H_CH_CRC_H_
#define H_CH_CRC_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint16_t CRC16(uint8_t *puchMsgg, uint16_t usDataLen);

// modbus crc
uint16_t CalcCRC(uint8_t *Buffer, uint8_t u8length);

#endif /* INC_CHTOOLS_H_ */
