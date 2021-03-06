#ifndef ESP8266TSLOGGER_H
#define ESP8266TSLOGGER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if defined(ESP8266)

	#include <SoftwareSerial.h>

	class ESP8266TsLogger {
	public:
		ESP8266TsLogger();
		~ESP8266TsLogger();
		
		static void init(uint8_t txPin, uint8_t rxPin, unsigned long baudRate=115200);
		
		static void postData(String wwwFormEncodedPayload);
		
		static String readData();
		
	private:
		static SoftwareSerial* ss;
	};

#endif
	
#endif // ESP8266TSLOGGER_H