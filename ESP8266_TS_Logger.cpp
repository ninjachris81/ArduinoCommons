#include "ESP8266_TS_Logger.h"

SoftwareSerial* ESP8266TsLogger::ss = NULL;

ESP8266TsLogger::ESP8266TsLogger() {
}

ESP8266TsLogger::~ESP8266TsLogger() {
	delete ss;
}

void ESP8266TsLogger::init(uint8_t rxPin, uint8_t txPin, unsigned long baudRate) {
	ss = new SoftwareSerial(rxPin, txPin);
	ss->begin(baudRate);
}

void ESP8266TsLogger::postData(String wwwFormEncodedPayload) {
	ss->println(wwwFormEncodedPayload);
}

String ESP8266TsLogger::readData() {
	if (ss->available() > 0) {
		return ss->readString();
	} else {
		return "";
	}
}