#ifndef BEHAVIORPROPERTY_H
#define BEHAVIORPROPERTY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Property.h"

template < typename VALUE_TYPE >
class BehaviorProperty : public Property<VALUE_TYPE> {
public:
	BehaviorProperty() {
	}
	
	void init(uint8_t id, VALUE_TYPE initialValue = 0, int32_t minChangeMs = 0) {
		Property<VALUE_TYPE>::init(id, initialValue);
		this->minChangeMs = minChangeMs;
		this->toSetValue = initialValue;
		this->lastChange = millis();
	}
	
	void update() {
		if (toSetValue!=this->value && millis() - lastChange >= minChangeMs) {
			return this->_setValue(toSetValue);
			
			lastChange = millis();
		}
	}
	
	bool setValue(VALUE_TYPE value) {
		if (minChangeMs==0) {
			return this->_setValue(value, false);
		} else {
			toSetValue = value;
			return false;
		}
	}
	
private:
	VALUE_TYPE toSetValue;
	int32_t minChangeMs = 0;
	unsigned long lastChange = 0;
};


#endif