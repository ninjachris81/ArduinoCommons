#ifndef SMOOTHVALUE_H
#define SMOOTHVALUE_H

#include <LogHelper.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define SMOOTH_SIZE 10
#define INIT_ZERO_VALUE 0.0

class SmoothValue {
	
public:
	SmoothValue(uint8_t smoothSize = SMOOTH_SIZE, float initValue = INIT_ZERO_VALUE) {
		init(smoothSize, initValue);
	}
	
	void init(uint8_t smoothSize, float initValue) {
		this->smoothSize = smoothSize;
		values = new float[smoothSize];
		for (uint8_t i=0;i<smoothSize;i++) values[i] = initValue;
		mInitValue = initValue;
	}

	float getValue() {
	  double returnValue = 0.0;
	  uint8_t vCount = 0;
	  
	  for (uint8_t i=0;i<smoothSize;i++) {
		if (values[i]==mInitValue) continue;
		returnValue+=values[i];
		vCount++;
	  }
	  
	  if (vCount==0) return mInitValue;	  
	  return (returnValue / vCount);
  }
	
	void pushValue(float value) {
	  values[valueIndex] = value;
	  valueIndex++;
	  if (valueIndex>=smoothSize) valueIndex = 0;
	}
	
	void printValues() {
		LOG_PRINTLN(F("-----------"));
	  for (uint8_t i=0;i<smoothSize;i++) {
		  LOG_PRINTLN(values[i]);
	  }
		LOG_PRINTLN(F("-----------"));
		LOG_PRINTLN(getValue());
		LOG_PRINTLN(F("-----------"));
	}
	
	
protected:
	uint8_t smoothSize = SMOOTH_SIZE;
	uint8_t valueIndex = 0;
	float* values;
	float mInitValue = INIT_ZERO_VALUE;
	
};
	
#endif