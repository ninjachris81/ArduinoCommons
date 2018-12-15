#ifndef LOG_H
#define LOG_H

//#define NO_LOG_SERIAL
//#define LOG_PREFIX '/'		// enable prefix
#define LOG_SERIAL_DEV Serial

#ifndef NO_LOG_SERIAL
	#define LOG_INIT() LOG_SERIAL_DEV.begin(115200)
	#define LOG_INIT2(baudrate) LOG_SERIAL_DEV.begin(baudrate)
	#define LOG_WAIT() while(!LOG_SERIAL_DEV) {delay(10);}

	#ifdef LOG_PREFIX
	  #define LOG_PRINT(msg) LOG_SERIAL_DEV.print(LOG_PREFIX); LOG_SERIAL_DEV.print(msg)
	  #define LOG_PRINTLN(msg) LOG_SERIAL_DEV.print(LOG_PREFIX); LOG_SERIAL_DEV.println(msg)
	#else
	  #define LOG_PRINT(msg) LOG_SERIAL_DEV.print(msg)
	  #define LOG_PRINTLN(msg) LOG_SERIAL_DEV.println(msg)
	#endif
	  
	#ifdef LOG_PREFIX
	  #define LOG_PRINTF(msg, format) LOG_SERIAL_DEV.print(LOG_PREFIX); LOG_SERIAL_DEV.print(msg, format)
	  #define LOG_PRINTLNF(msg, format) LOG_SERIAL_DEV.print(LOG_PREFIX); LOG_SERIAL_DEV.println(msg, format)
	#else
	  #define LOG_PRINTF(msg, format) LOG_SERIAL_DEV.print(msg, format)
	  #define LOG_PRINTLNF(msg, format) LOG_SERIAL_DEV.println(msg, format)
	#endif
  
#else
	#define LOG_INIT()
	#define LOG_INIT2(baudrate)
	#define LOG_WAIT()
	#define LOG_PRINT(msg)
	#define LOG_PRINTLN(msg)

	#define LOG_PRINTF(msg, format)
	#define LOG_PRINTLNF(msg, format)
#endif

#endif    // LOG_H
