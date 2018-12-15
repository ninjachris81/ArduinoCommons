#ifndef PROPERTY_H
#define PROPERTY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "LogHelper.h"

#define MAX_VALUE_CHANGE_LISTENERS 6

//#define SUPPORT_OUTPUT_ON_CHANGE
//#define SUPPORT_PROPERTY_NAME
//#define SUPPORT_SIMULATION

template < typename VALUE_TYPE >
class Property {
public:

	class ValueChangeListener {
	public:
		virtual void onPropertyValueChange(uint8_t id, VALUE_TYPE newValue, VALUE_TYPE oldValue) = 0;
	};
	
	Property() {
	}

	Property(uint8_t id, VALUE_TYPE initialValue = 0) {
		init(id, initialValue);
	}

	void init(uint8_t id, VALUE_TYPE initialValue = 0) {
		this->id = id;
		this->value = initialValue;
#ifdef SUPPORT_PROPERTY_NAME
		this->name = "";
#endif
	}

#ifdef SUPPORT_PROPERTY_NAME
	void init(uint8_t id, String name, VALUE_TYPE initialValue = 0) {
		this->id = id;
		this->value = initialValue;
		this->name = name;
	}
#endif

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
	
	void fireChangeEvent() {
		for (uint8_t i=0; i<listenerCount; i++) {
		  valueChangeListeners[i]->onPropertyValueChange(id, value, value);
		}
	}
	
#ifdef SUPPORT_OUTPUT_ON_CHANGE
	void setOutputOnChange(bool outputChange) {
		this->outputChange = outputChange;
	}
#endif
  
#ifdef SUPPORT_PROPERTY_NAME
	void setName(String name) {
		this->name = name;
	}
#endif

private:
	uint8_t id = 0;
	
#ifdef SUPPORT_SIMULATION
	bool simulated = false;
#endif
	
#ifdef SUPPORT_OUTPUT_ON_CHANGE
	bool outputChange = false;
#endif

#ifdef SUPPORT_PROPERTY_NAME
	String name;
#endif
	
	ValueChangeListener* valueChangeListeners[MAX_VALUE_CHANGE_LISTENERS];
	uint8_t listenerCount = 0;

	
protected:
	VALUE_TYPE value;

	bool _setValue(VALUE_TYPE value, bool fromSimulated = false) {
#ifdef SUPPORT_SIMULATION
		if (this->simulated && !fromSimulated) return false;			// ignore
#endif

		if (this->value!=value) {
			VALUE_TYPE oldValue = this->value;
			this->value = value;

			invokeListeners(value, oldValue);
			
#ifdef SUPPORT_OUTPUT_ON_CHANGE
			if (outputChange) {
#ifdef SUPPORT_PROPERTY_NAME
				LOG_PRINT(name);
				LOG_PRINT(" ");
#endif
				LOG_PRINT(id);
				LOG_PRINT(F(" -> "));
				LOG_PRINTLN(value);
			}
#endif			
			
			return true;
		} else {
			return false;
		}
	}

	void invokeListeners(VALUE_TYPE value, VALUE_TYPE oldValue) {
		for (uint8_t i=0; i<listenerCount; i++) {
		  valueChangeListeners[i]->onPropertyValueChange(id, value, oldValue);
		}
	}

	
};

#endif
