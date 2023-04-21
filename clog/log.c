/*
 * log.c
 *
 *  Created on: 2021年7月1日
 *      Author: Administrator
 */

#include "log.h"

#include <stdarg.h>
#include <stdio.h>

#include "data.h"

/**
 * output lock
 */
void log_port_output_lock(void) {}

/**
 * output unlock
 */
void log_port_output_unlock(void) {
  /* add your code here */
}

void MyPrintf(const char *format, ...) {
  log_port_output_lock();
  SYSTEM_TIME_T time = GetTime();
  static char a[40] = {0};
  snprintf(a, 40, "20%02d-%02d-%02d %02d:%02d:%02d", time.Year, time.Mouth, time.Date, time.Hours, time.Minutes, time.Seconds);
  clog_v("[%s]\t", a);
  va_list args;            // 定义一个va_list类型的变量，用来储存单个参数
  va_start(args, format);  // 使args指向可变参数的第一个参数
  vprintf(format, args);   // 必须用vprintf等带V的
  va_end(args);            // 结束可变参数的获取
  clog_v("\r\n");
  log_port_output_unlock();
}
