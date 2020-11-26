#ifndef FIVEKEYSHANDLER_H
#define FIVEKEYSHANDLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ANALOG_READ_CYCLES 5

#define ANALOG_BTN_NONE 0
#define ANALOG_BTN_LEFT 1
#define ANALOG_BTN_UP 2
#define ANALOG_BTN_DOWN 3
#define ANALOG_BTN_RIGHT 4
#define ANALOG_BTN_ENTER 5

class FiveKeysHandler {
public:
	FiveKeysHandler(uint8_t analogPin);
	
	class FKFeedbackHandler {
	public:
		virtual void onLeft(bool isDown) = 0;
		virtual void onRight(bool isDown) = 0;
		virtual void onUp(bool isDown) = 0;
		virtual void onDown(bool isDown) = 0;
		virtual void onPressed(bool isDown) = 0;
	};
	
	void init(FKFeedbackHandler* handler);
	
	void update();
	
private:
	FKFeedbackHandler* handler = NULL;
	uint8_t analogPin = 0;
	uint8_t lastButton = ANALOG_BTN_NONE;
	
	void callHandler(uint8_t btn, bool isDown);
};


#endif		// FIVEKEYSHANDLER_H