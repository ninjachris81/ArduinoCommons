#ifndef ESP8266TSLOGGER_H
#define ESP8266TSLOGGER_H

#include <SoftwareSerial.h>

class ESP8266TsLogger {
public:
	ESP8266TsLogger();
	~ESP8266TsLogger();
	
	static void init(uint8_t txPin, uint8_t rxPin, int baudRate=9600);
	
	static void postData(String wwwFormEncodedPayload);
	
private:
	static SoftwareSerial* ss;
};

#endif // ESP8266TSLOGGER_H