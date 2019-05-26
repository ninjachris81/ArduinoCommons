#ifndef FLOATPROPERTY_H
#define FLOATPROPERTY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Property.h"

class FloatProperty : public Property<float> {
public:
	FloatProperty() {
	}
	
	bool setValue(float newValue) {
		if (abs(value-newValue)>tolerance) {
			return _setValue(newValue, false);
		}
	}
	
	void setTolerance(float newTolerance) {
		tolerance = newTolerance;
	}
	
private:
	float tolerance = 0;
};

#endif