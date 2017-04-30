#ifndef LOG_H
#define LOG_H

//#define NO_SERIAL

#ifndef NO_SERIAL
  #define LOG_INIT() Serial.begin(115200)
  #define LOG_PRINT(msg) Serial.print(msg)
  #define LOG_PRINTLN(msg) Serial.println(msg)
  
  #define LOG_PRINTF(msg, format) Serial.println(msg, format)
  #define LOG_PRINTLNF(msg, format) Serial.println(msg, format)
#else
  #define LOG_INIT()
  #define LOG_PRINT(msg)
  #define LOG_PRINTLN(msg)
  
  #define LOG_PRINTF(msg, format)
  #define LOG_PRINTLNF(msg, format)
#endif

#endif    // LOG_H
