/*
 * @Author: ch
 * @Description:
 * @Date: 2021-04-08 18:57:01
 * @LastEditTime: 2021-04-11 17:02:28
 * @LastEditors: ch
 * @version:
 * @Reference:
 */
#ifndef CH_QUEUE_H
#define CH_QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#define QUEUE_BUF_SIZE         1400
#define MESSAGE_QUEUE_BUF_SIZE 100

#define MQ_LOG_ENABLE          1
#define MQ_LOG_LEVEL           2

#define MQ_LOG_LEVEL_E         5
#define MQ_LOG_LEVEL_W         4
#define MQ_LOG_LEVEL_D         3
#define MQ_LOG_LEVEL_I         2
#define MQ_LOG_LEVEL_V         1

#define mq_log(TAG, ...) \
  do {                   \
    printf("%s:", TAG);  \
    printf(__VA_ARGS__); \
    printf("\r\n");      \
  } while (0)

#define mq_log_hex(TAG, descriptioin, data, len) \
  do {                                           \
    printf("%s:%s", TAG, descriptioin);          \
    for (int i = 0; i < len; i++) {              \
      if (i % 20 == 0) {                         \
        printf("\r\n");                          \
      }                                          \
      printf("%02X ", data[i]);                  \
    }                                            \
    printf("\r\n");                              \
  } while (0)

typedef struct {
  uint8_t *data;
  uint16_t len;
  uint8_t *argv;
  size_t argvSize;
  uint8_t ready;
} QueueBuf_t;

typedef struct {
  QueueBuf_t queuebuf[MESSAGE_QUEUE_BUF_SIZE];
  int readIdx;
  int writeIdx;

} messageQueue_t;

typedef enum {
  mqOK = 0,
  mqError = -1,
  mqErrorOverflow = 2,        // buff size is to long
  mqStatusBuffFull = 3,       // buff is full
  mqErrorNotEnoughSpace = 4,  // memery allocation failed
  mqStatusEmpty,              // mq is empty
  mqStatusNotEmpty,           // mq is not empyt
  mqStatusNotInit,            // mq is not init
} mqStatus_t;

typedef void (*MQPacketArrived)(uint8_t *packet, uint16_t packetLen, uint8_t *arg, size_t argvSize);

typedef struct {
  messageQueue_t mq;
  MQPacketArrived deliver_packet;
  void *arg;
} messageQueueHandler;

#ifdef __cplusplus
extern "C" {
#endif

void MQInit(messageQueueHandler *self, MQPacketArrived pHandlerPacket);
void MQRecvData(messageQueueHandler *self);
mqStatus_t MQEnqueue(messageQueueHandler *self, uint8_t *data, uint16_t size, uint8_t *argv, size_t argvSize);
void PacketPoll(messageQueueHandler *mq);

#ifdef __cplusplus
}
#endif
#endif  // !CH_QUEUE_H
