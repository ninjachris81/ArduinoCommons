#ifndef LOG_H
#define LOG_H

//#define NO_LOG_SERIAL

#ifndef NO_LOG_SERIAL
  #define LOG_INIT() Serial.begin(115200)
  #define LOG_INIT2(baudrate) Serial.begin(baudrate)
  #define LOG_WAIT() while(!Serial) {delay(10);}
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
