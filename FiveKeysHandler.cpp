#include "FiveKeysHandler.h"


FiveKeysHandler::FiveKeysHandler(uint8_t analogPin) {
	this->analogPin = analogPin;
	this->lastButton = ANALOG_BTN_NONE;
}

void FiveKeysHandler::init(FKFeedbackHandler* handler) {
	this->handler = handler;
}

void FiveKeysHandler::update() {
	if (handler==NULL) return;
	
	uint8_t button = ANALOG_BTN_NONE;
	int sum = 0;

	for (uint8_t i = 0; i < ANALOG_READ_CYCLES; i++) {
		sum += analogRead(analogPin);
	}
	int v = sum / ANALOG_READ_CYCLES;
  
	if (v >= 0  && v < 20)  button = ANALOG_BTN_LEFT; //LEFT
	else if (v > 2 && v < 40) button = ANALOG_BTN_UP; //UP
	else if (v > 80 && v < 90) button = ANALOG_BTN_DOWN; //DOWN
	else if (v > 160 && v < 170) button = ANALOG_BTN_RIGHT; //RIGHT
	else if (v > 340 && v < 350) button = ANALOG_BTN_ENTER; //ENTER
	
	
	if (button!=this->lastButton) {
		if (this->lastButton!=ANALOG_BTN_NONE) callHandler(this->lastButton, false);
		callHandler(button, true);
		
		this->lastButton = button;
	}
	
}

void FiveKeysHandler::callHandler(uint8_t btn, bool isDown) {
	switch(btn) {
		case ANALOG_BTN_LEFT:
			handler->onLeft(isDown);
			break;
		case ANALOG_BTN_UP:
			handler->onUp(isDown);
			break;
		case ANALOG_BTN_DOWN:
			handler->onDown(isDown);
			break;
		case ANALOG_BTN_RIGHT:
			handler->onRight(isDown);
			break;
		case ANALOG_BTN_ENTER:
			handler->onPressed(isDown);
			break;
	}
}