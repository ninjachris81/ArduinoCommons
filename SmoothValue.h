#ifndef SMOOTHVALUE_H
#define SMOOTHVALUE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define SMOOTH_SIZE 10
#define ZERO_VALUE 0

class SmoothValue {
	
public:
	SmoothValue() {
		for (uint8_t i=0;i<SMOOTH_SIZE;i++) values[i] = ZERO_VALUE;
	}

	float getValue() {
	  double returnValue = 0.0;
	  uint8_t vCount = 0;
	  
	  for (uint8_t i=0;i<SMOOTH_SIZE;i++) {
		if (values[i]==0) break;
		returnValue+=values[i];
		vCount++;
	  }
	  
	return (returnValue / vCount);
  }
	
	void pushValue(float value) {
	  values[valueIndex] = value;
	  valueIndex++;
	  if (valueIndex>=SMOOTH_SIZE) valueIndex = 0;
	}
	
	
protected:
	uint8_t valueIndex = 0;
	float values[SMOOTH_SIZE];
	
};
	
#endif