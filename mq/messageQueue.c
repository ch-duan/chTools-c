/*
 * @Author: ch
 * @Description:
 * @Date: 2021-04-08 18:56:55
 * @LastEditTime: 2021-04-12 12:28:46
 * @LastEditors: ch
 * @version:
 * @Reference:
 */
#include "messageQueue.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAG "MQ"

static void InitChQueueBuf(messageQueue_t *mq);
static mqStatus_t isEmpty(messageQueue_t *mq);

static mqStatus_t deleteElement(messageQueue_t *mq, uint8_t idx);
static mqStatus_t dequeue(messageQueue_t *mq);
mqStatus_t enqueue(messageQueue_t *mq, uint8_t *data, uint16_t size, uint8_t *argv, size_t argvSize);
static mqStatus_t GetReadyChQueueBuf(messageQueue_t *mq, uint8_t **data, uint16_t *size, uint8_t **argv, size_t *argvSize);

void InitChQueueBuf(messageQueue_t *mq) {
  memset(mq->queuebuf, 0, MESSAGE_QUEUE_BUF_SIZE * sizeof(QueueBuf_t));
  mq->readIdx = 0;
  mq->writeIdx = 0;
}

static mqStatus_t isEmpty(messageQueue_t *mq) {
  return mq->readIdx == mq->writeIdx ? mqStatusEmpty : mqStatusNotEmpty;
}

static mqStatus_t deleteElement(messageQueue_t *mq, uint8_t idx) {
  if (mq == NULL) {
    return mqError;
  }
  if (mq->queuebuf[idx].data != NULL) {
    free(mq->queuebuf[idx].data);
  }
  if (mq->queuebuf[idx].argv != NULL) {
    free(mq->queuebuf[idx].argv);
  }
  mq->queuebuf[idx].data = NULL;
  mq->queuebuf[idx].ready = 0;
  mq->queuebuf[idx].len = 0;
  mq->queuebuf[idx].argv = NULL;
  mq->queuebuf[idx].argvSize = 0;
  return mqOK;
}

static mqStatus_t dequeue(messageQueue_t *mq) {
  if (mq == NULL) {
    return mqError;
  }
  int nextIdx = (mq->readIdx + 1) % MESSAGE_QUEUE_BUF_SIZE;
  if (mq->readIdx == mq->writeIdx) {
#if MQ_LOG_ENABLE
#if MQ_LOG_LEVEL >= MQ_LOG_LEVEL_I
    mq_log(TAG, "empty queue:%d\r\n", mq->readIdx);
#endif
#endif
    // empty queue
    return mqError;
  }
  if (deleteElement(mq, mq->readIdx) == mqError) {
    return mqError;
  }
  mq->readIdx = nextIdx;
#if MQ_LOG_ENABLE
#if MQ_LOG_LEVEL >= MQ_LOG_LEVEL_I
  mq_log(TAG, "dequeue idx:%d\r\n", mq->readIdx);
#endif
#endif
  return mqOK;
}

mqStatus_t enqueue(messageQueue_t *mq, uint8_t *data, uint16_t size, uint8_t *argv, size_t argvSize) {
  // mq is not init.
  if (mq == NULL) {
    return mqStatusNotInit;
  }
  if (size > QUEUE_BUF_SIZE) {
    return mqErrorOverflow;
  }

  int nextIdx = (mq->writeIdx + 1) % MESSAGE_QUEUE_BUF_SIZE;
  if (nextIdx == mq->readIdx) {
#if MQ_LOG_ENABLE
#if MQ_LOG_LEVEL >= MQ_LOG_LEVEL_I
    mq_log(TAG, "mq buff full,%d,%d\r\n", mq->writeIdx, mq->readIdx);
#endif
#endif
    return mqStatusBuffFull;
  }

  mq->queuebuf[mq->writeIdx].len = size;
  mq->queuebuf[mq->writeIdx].argvSize = argvSize;
  if (mq->queuebuf[mq->writeIdx].data != NULL) {
    free(mq->queuebuf[mq->writeIdx].data);
    mq->queuebuf[mq->writeIdx].data = NULL;
  }
  if (size != 0) {
    mq->queuebuf[mq->writeIdx].data = (uint8_t *) malloc(size);
    if (mq->queuebuf[mq->writeIdx].data == NULL) {
      mq_log(TAG, "No memory for buffer.\r\n");
      return mqErrorNotEnoughSpace;
    }
    memcpy(mq->queuebuf[mq->writeIdx].data, data, size);
  }

  if (mq->queuebuf[mq->writeIdx].argv != NULL) {
    free(mq->queuebuf[mq->writeIdx].argv);
    mq->queuebuf[mq->writeIdx].argv = NULL;
  }
  if (argvSize != 0) {
    mq->queuebuf[mq->writeIdx].argv = (uint8_t *) malloc(argvSize);
    if (mq->queuebuf[mq->writeIdx].argv == NULL) {
      mq_log(TAG, "No memory for buffer.\r\n");
      return mqErrorNotEnoughSpace;
    }
    memcpy(mq->queuebuf[mq->writeIdx].argv, argv, argvSize);
  }
  mq->queuebuf[mq->writeIdx].ready = 1;

#if MQ_LOG_ENABLE
#if MQ_LOG_LEVEL >= MQ_LOG_LEVEL_D
  mq_log(TAG, "enqueue success:writeIdx:%d,ready:%d,%p,%p\r\n", mq->writeIdx, mq->queuebuf[mq->writeIdx].ready, data, mq->queuebuf[mq->writeIdx].data);
  mq_log(TAG, "enqueue write data :\t");
  for (int i = 0; i < mq->queuebuf[mq->writeIdx].len; i++) {
    printf("%02x ", *(mq->queuebuf[mq->writeIdx].data + i));
  }
#endif
#endif
  mq->queuebuf[nextIdx].ready = 0;
  mq->writeIdx = nextIdx;
  return mqOK;
}

static mqStatus_t GetReadyChQueueBuf(messageQueue_t *mq, uint8_t **data, uint16_t *size, uint8_t **argv, size_t *argvSize) {
  if (isEmpty(mq) == mqStatusEmpty) {
    return mqError;
  }

  if (mq->queuebuf[mq->readIdx].ready == 0) {
    return mqError;
  }
  *size = mq->queuebuf[mq->readIdx].len;
  *argvSize = mq->queuebuf[mq->readIdx].argvSize;

  if (mq->queuebuf[mq->readIdx].len > QUEUE_BUF_SIZE) {
    return mqError;
  }

  if (*data == NULL) {
    *data = (uint8_t *) malloc(*size);
    if (*data == NULL) {
      mq_log(TAG, "No memory for buffer.\r\n");
      return mqErrorNotEnoughSpace;
    }
  }
  memcpy(*data, mq->queuebuf[mq->readIdx].data, mq->queuebuf[mq->readIdx].len);
  if (*argv == NULL) {
    *argv = (uint8_t *) malloc(*argvSize);
    if (*argv == NULL) {
      mq_log(TAG, "No memory for buffer.\r\n");
      return mqErrorNotEnoughSpace;
    }
  }
  memcpy(*argv, mq->queuebuf[mq->readIdx].argv, mq->queuebuf[mq->readIdx].argvSize);

  // dequeue
  dequeue(mq);
  return mqOK;
}

void MQInit(messageQueueHandler *self, MQPacketArrived pHandlerPacket) {
  InitChQueueBuf(&self->mq);
  self->arg = self;
  self->deliver_packet = pHandlerPacket;
}

void MQRecvData(messageQueueHandler *self) {
  uint8_t *buf = NULL;
  uint16_t len = 0;
  uint8_t *argv = NULL;
  size_t argvSize = 0;
  if (GetReadyChQueueBuf(&self->mq, &buf, &len, &argv, &argvSize) != mqOK) {
    return;
  }
  //  if (len == 0) {
  //    return;
  //  }

  self->deliver_packet(buf, len, argv, argvSize);
  if (buf != NULL) {
    free(buf);
    buf = NULL;
  }
  if (argv != NULL) {
    free(argv);
    argv = NULL;
  }
}

mqStatus_t MQEnqueue(messageQueueHandler *self, uint8_t *data, uint16_t size, uint8_t *argv, size_t argvSize) {
  return enqueue(&self->mq, data, size, argv, argvSize);
}

void PacketPoll(messageQueueHandler *mq) {
  MQRecvData(mq);
}
