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
		value.pushValue(getRaw());
	}
	
	float getValueC() {
		return toCelsius(value.getValue());
	}
	
	float getValueF() {
		return celsiusToFahrenheit(toCelsius(value.getValue()));
	}

	float toCelsius(float RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
		return toCelsius(RawADC, knownR);
	}
	
	static float toCelsius(float RawADC, float knownR) {  //Function to perform the fancy math of the Steinhart-Hart equation
		double Temp;
		//Temp = log(((10240000/RawADC) - knownR));
		Temp = log(10000.0*((1024.0/RawADC-1))); 		// TODO: knownR
		Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
		Temp = Temp - 273.15;              // Convert Kelvin to Celsius
		//Temp = (Temp * 9.0)/ 5.0 + 32.0;
		return Temp;
	}
	
	static float celsiusToFahrenheit(float tempC) {
		return (tempC * 9.0)/ VOLTAGE_IN + 32.0; // Celsius to Fahrenheit - comment out this line if you need Celsius
	}

private:
	float knownR;
	
};

#endif		// ANALOGTEMPSENSOR_H