#ifndef BROADCASTPROPERTY_H
#define BROADCASTPROPERTY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Property.h"

template < typename VALUE_TYPE >
class BroadcastProperty : public Property<VALUE_TYPE> {
	
public:
	BroadcastProperty() {
	}
	
	void init(uint8_t id, VALUE_TYPE initialValue = 0, int32_t broadcastInterval = 0) {
		Property<VALUE_TYPE>::init(id, initialValue);
		this->broadcastInterval = broadcastInterval;
		this->lastChange = broadcastInterval;
	}
	
	bool setValue(VALUE_TYPE value, bool enableBC) {
		if (enableBC) {
			 enableBC = true;
		}
		
		return setValue(value);
	}

	bool setValue(VALUE_TYPE value) {
		if (Property<VALUE_TYPE>::setValue(value)) {
			lastChange = millis();
			return true;
		} else {
			// else, it will not update the ts, so that bc will be sent if no change over long time
			return false;
		}
	}
	
	void update() {
		if (sendBC && (millis() - lastChange > broadcastInterval)) {
			Property<VALUE_TYPE>::fireChangeEvent();
			lastChange = millis();
		}
	}
	
	void enableBroadcast() {
		sendBC = true;
		lastChange = millis();
	}
	
	void disableBroadcast() {
		sendBC = false;
	}
	
private:
	int32_t broadcastInterval = 0;
	int64_t lastChange;
	bool sendBC = true;
};

#endif