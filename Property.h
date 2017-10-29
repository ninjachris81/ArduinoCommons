#ifndef PROPERTY_H
#define PROPERTY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define MAX_VALUE_CHANGE_LISTENERS 6

template < typename VALUE_TYPE >
class Property {
public:

	class ValueChangeListener {
	public:
		virtual void onPropertyValueChange(uint8_t id, VALUE_TYPE value) = 0;
	};
	
	Property() {
	}

	Property(uint8_t id, VALUE_TYPE initialValue = 0) {
		init(id, initialValue);
	}

	void init(uint8_t id, VALUE_TYPE initialValue = 0) {
		this->id = id;
		this->value = initialValue;
	}

	VALUE_TYPE getValue() {
		return this->value;
	}
	
	bool setValue(VALUE_TYPE value) {
		return _setValue(value, false);
	}
	
	void setSimulatedValue(VALUE_TYPE value) {
		this->simulated = true;
		_setValue(value, true);
	}
	
	void setSimulationOff() {
		this->simulated = false;
	}

	void registerValueChangeListener(ValueChangeListener* listener) {
		if (listenerCount>=MAX_VALUE_CHANGE_LISTENERS) return;
		valueChangeListeners[listenerCount] = listener;
		listenerCount++;
	}
  
private:
	uint8_t id = 0;
	VALUE_TYPE value;
	bool simulated = false;
  
	ValueChangeListener* valueChangeListeners[MAX_VALUE_CHANGE_LISTENERS];
	uint8_t listenerCount = 0;

	
	bool _setValue(VALUE_TYPE value, bool fromSimulated) {
		if (this->simulated && !fromSimulated) return false;			// ignore
		
		if (this->value!=value) {
			this->value = value;

			for (uint8_t i=0; i<listenerCount; i++) {
			  valueChangeListeners[i]->onPropertyValueChange(id, value);
			}
			return true;
		} else {
			return false;
		}
	}
	
};

#endif
