#ifndef ANIMATEDPROPERTY_H
#define ANIMATEDPROPERTY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Property.h"

template < typename VALUE_TYPE >
class AnimatedProperty : public Property<VALUE_TYPE> {
public:
	AnimatedProperty() {
	}
	
	void init(uint8_t id, VALUE_TYPE initialValue = 0, int32_t animationSpeed = 0, VALUE_TYPE animationDelta = 0) {
		Property<VALUE_TYPE>::init(id, initialValue);
		this->animationSpeed = animationSpeed;
		this->animationDelta = animationDelta;
		this->toSetValue = initialValue;
	}
	
	void update() {
		if (animationDelta>0 && toSetValue!=this->value) {
			if (toSetValue < this->value) {
				this->_setValue(max(toSetValue, this->value - animationDelta));
			} else {
				this->_setValue(min(toSetValue, this->value + animationDelta));
			}
		} else if (animationDelta>0 && animationSpeed!=0) {
			// reset
			animationDelta = 0;
		}
	}
	
	bool setValue(VALUE_TYPE value) {
		if (animationDelta==0 && animationSpeed==0) {
			return this->_setValue(value);
		} else if (animationSpeed!=0) {
			animationDelta = abs(toSetValue - value) / animationSpeed;
			toSetValue = value;
			return false;
		} else if (animationDelta!=0) {
			toSetValue = value;
			return false;
		}
	}
	
	bool isAnimating() {
		return toSetValue!=this->value;
	}
	
private:
	VALUE_TYPE toSetValue;
	VALUE_TYPE animationDelta;
	VALUE_TYPE animationSpeed = 0;
};


#endif
