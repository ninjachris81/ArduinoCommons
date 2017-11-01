#ifndef ANALOGTEMPSENSOR_H
#define ANALOGTEMPSENSOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "AnalogSensor.h"

#define VOLTAGE_IN 5.0

class AnalogTempSensor : public AnalogSensor {
	
public:
	AnalogTempSensor(int addr = -1, uint8_t smoothSize = SMOOTH_SIZE, float initValue = INIT_ZERO_VALUE, float knownR = 0) : AnalogSensor(addr, smoothSize, initValue) {
		init(addr, smoothSize, initValue, knownR);
	}
	
	void init(int addr, uint8_t smoothSize, float initValue, float knownR) {
		if (addr>=0 && knownR>0) {
			this->knownR = knownR;
			AnalogSensor::init(addr, smoothSize, initValue);
		}
	}
	
	void read() {
		value.pushValue(knownR * ((VOLTAGE_IN/((getRaw() * VOLTAGE_IN)/1024.0)) -1));
	}
	
private:
	float knownR;
	
};

#endif		// ANALOGTEMPSENSOR_H