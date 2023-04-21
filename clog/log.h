/*
 * log.h
 *
 *  Created on: 2021年7月1日
 *      Author: Administrator
 */

#ifndef INC_LOG_H_
#define INC_LOG_H_

#include <string.h>

#if CONFIG_LOG_COLORS
#define LOG_COLOR_BLACK  "30"
#define LOG_COLOR_RED    "31"
#define LOG_COLOR_GREEN  "32"
#define LOG_COLOR_BROWN  "33"
#define LOG_COLOR_BLUE   "34"
#define LOG_COLOR_PURPLE "35"
#define LOG_COLOR_CYAN   "36"
#define LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)  "\033[1;" COLOR "m"
#define LOG_RESET_COLOR  "\033[0m"
#define LOG_COLOR_E      LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W      LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I      LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V
#else
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR
#endif

#define LOG_FORMAT(letter, format)             LOG_COLOR_##letter #letter " (%u) %s: " format LOG_RESET_COLOR "\n"
#define LOG_SYSTEM_TIME_FORMAT(letter, format) LOG_COLOR_##letter #letter " (%s) %s: " format LOG_RESET_COLOR "\n"

#if CONFIG_LOG_TIMESTAMP_SOURCE_RTOS
#define ESP_LOG_LEVEL(level, tag, format, ...)                                                             \
  do {                                                                                                     \
    if (level == ESP_LOG_ERROR) {                                                                          \
      esp_log_write(ESP_LOG_ERROR, tag, LOG_FORMAT(E, format), esp_log_timestamp(), tag, ##__VA_ARGS__);   \
    } else if (level == ESP_LOG_WARN) {                                                                    \
      esp_log_write(ESP_LOG_WARN, tag, LOG_FORMAT(W, format), esp_log_timestamp(), tag, ##__VA_ARGS__);    \
    } else if (level == ESP_LOG_DEBUG) {                                                                   \
      esp_log_write(ESP_LOG_DEBUG, tag, LOG_FORMAT(D, format), esp_log_timestamp(), tag, ##__VA_ARGS__);   \
    } else if (level == ESP_LOG_VERBOSE) {                                                                 \
      esp_log_write(ESP_LOG_VERBOSE, tag, LOG_FORMAT(V, format), esp_log_timestamp(), tag, ##__VA_ARGS__); \
    } else {                                                                                               \
      esp_log_write(ESP_LOG_INFO, tag, LOG_FORMAT(I, format), esp_log_timestamp(), tag, ##__VA_ARGS__);    \
    }                                                                                                      \
  } while (0)
#elif CONFIG_LOG_TIMESTAMP_SOURCE_SYSTEM
#define ESP_LOG_LEVEL(level, tag, format, ...)                                                                                \
  do {                                                                                                                        \
    if (level == ESP_LOG_ERROR) {                                                                                             \
      esp_log_write(ESP_LOG_ERROR, tag, LOG_SYSTEM_TIME_FORMAT(E, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__);   \
    } else if (level == ESP_LOG_WARN) {                                                                                       \
      esp_log_write(ESP_LOG_WARN, tag, LOG_SYSTEM_TIME_FORMAT(W, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__);    \
    } else if (level == ESP_LOG_DEBUG) {                                                                                      \
      esp_log_write(ESP_LOG_DEBUG, tag, LOG_SYSTEM_TIME_FORMAT(D, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__);   \
    } else if (level == ESP_LOG_VERBOSE) {                                                                                    \
      esp_log_write(ESP_LOG_VERBOSE, tag, LOG_SYSTEM_TIME_FORMAT(V, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__); \
    } else {                                                                                                                  \
      esp_log_write(ESP_LOG_INFO, tag, LOG_SYSTEM_TIME_FORMAT(I, format), esp_log_system_timestamp(), tag, ##__VA_ARGS__);    \
    }                                                                                                                         \
  } while (0)
#endif  // CONFIG_LOG_TIMESTAMP_SOURCE_xxx

#define APPDEBUG     12
#define APPDEBUG_ALL 7
void MyPrintf(const char *format, ...);

void log_port_output_lock(void);
void log_port_output_unlock(void);

/*
 #define clog_v(format, args...) \
do{ \
  log_port_output_lock(); \
  MyPrintf("%s:%u %s\t" format"\r\n", __FILE__,  __LINE__,__FUNCTION__, ##args); \
  log_port_output_unlock(); \
}while(0)
 */

/*
 #define DBG2_PRINTF(...) \
do{ \
  log_port_output_lock(); \
  printf(__VA_ARGS__); \
  log_port_output_unlock(); \
}while(0)
 */
#define clog_v(format, ...)                                                                                                                        \
  printf("[20%02d-%02d-%02d %02d:%02d:%02d](%s:%u %s)\t" format "\r\n", sysTime.Year, sysTime.Mouth, sysTime.Date, sysTime.Hours, sysTime.Minutes, \
         sysTime.Seconds, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define clog_i(format, ...)                                                                                                                        \
  printf("[20%02d-%02d-%02d %02d:%02d:%02d](%s:%u %s)\t" format "\r\n", sysTime.Year, sysTime.Mouth, sysTime.Date, sysTime.Hours, sysTime.Minutes, \
         sysTime.Seconds, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define clog_d(format, ...)                                                                                                                        \
  printf("[20%02d-%02d-%02d %02d:%02d:%02d](%s:%u %s)\t" format "\r\n", sysTime.Year, sysTime.Mouth, sysTime.Date, sysTime.Hours, sysTime.Minutes, \
         sysTime.Seconds, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define clog_w(format, ...)                                                                                                                        \
  printf("[20%02d-%02d-%02d %02d:%02d:%02d](%s:%u %s)\t" format "\r\n", sysTime.Year, sysTime.Mouth, sysTime.Date, sysTime.Hours, sysTime.Minutes, \
         sysTime.Seconds, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define clog_e(format, ...)                                                                                                                        \
  printf("[20%02d-%02d-%02d %02d:%02d:%02d](%s:%u %s)\t" format "\r\n", sysTime.Year, sysTime.Mouth, sysTime.Date, sysTime.Hours, sysTime.Minutes, \
         sysTime.Seconds, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define clog_p1(format, ...)                                                                                                                                 \
  printf("[20%02d-%02d-%02d %02d:%02d:%02d](%s:%u %s)\t" format, sysTime.Year, sysTime.Mouth, sysTime.Date, sysTime.Hours, sysTime.Minutes, sysTime.Seconds, \
         __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define clog_p(...)      \
  do {                   \
    printf(__VA_ARGS__); \
  } while (0)

/*
 //#define clog_v(tag,format, ...)\
//  do{ \
//    if(strstr(tag,"%")!=NULL) {  \
//    MyPrintf("%s/%s:%u\t"tag, __FILE__, __FUNCTION__, __LINE__,format,##__VA_ARGS__);  \
//    } else { \
//      MyPrintf("%s\t%s/%s:%u\t"format,tag, __FILE__, __FUNCTION__, __LINE__,##__VA_ARGS__);  \
//    } \
//  }while(0)
 */

#endif /* INC_LOG_H_ */
