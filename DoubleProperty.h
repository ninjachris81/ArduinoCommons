#ifndef DOUBLEPROPERTY_H
#define DOUBLEPROPERTY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Property.h"

class DoubleProperty : public Property<double> {
public:
	DoubleProperty() {
	}
	
	bool setValue(double newValue) {
		if (abs(value-newValue)>tolerance) {
			return _setValue(newValue, false);
		}
	}
	
	void setTolerance(double newTolerance) {
		tolerance = newTolerance;
	}
	
private:
	double tolerance = 0;
};

#endif