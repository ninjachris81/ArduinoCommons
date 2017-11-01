#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SmoothValue.h"

class AnalogSensor {
	
public:
	AnalogSensor(int addr = -1, uint8_t smoothSize = SMOOTH_SIZE, float initValue = INIT_ZERO_VALUE) {
		init(addr, smoothSize, initValue);
	}
	
	void init(int addr, uint8_t smoothSize, float initValue) {
		if (addr>=0) {
			this->addr = addr;
			pinMode(addr,INPUT); 
			value.init(smoothSize, initValue);
		}
	}
	
	void read() {
		value.pushValue(getRaw());
	}
	
	float getRaw() {
		return analogRead(addr);
	}
	
protected:
	int addr;
	SmoothValue value;

};

#endif		// ANALOGSENSOR_H