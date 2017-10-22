#include "joystick_handler.h"


JoystickHandler::JoystickHandler(uint8_t pinX, uint8_t pinY, uint8_t pinBtn) {
  this->feedbackHandler = NULL;

  this->pinX = pinX;
  this->pinY = pinY;
  this->pinBtn = pinBtn;
  
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinBtn, INPUT);
}

void JoystickHandler::setFeedbackHandler(JoystickFeedbackHandler *feedbackHandler) {
  this->feedbackHandler = feedbackHandler;
}

void JoystickHandler::update() {
  short x = analogRead(pinX);
  short y = analogRead(pinY);
  uint8_t btn = digitalRead(pinBtn);

  //Serial.println(x, DEC);
  //Serial.println(y, DEC);

  if (btn==HIGH) {
    if (!BIT_CHECK(state,STATE_BUTTON)) {
      BIT_SET(state, STATE_BUTTON);
      if (feedbackHandler!=NULL) feedbackHandler->onPressed(true);
    }
  } else {
    if (BIT_CHECK(state,STATE_BUTTON)) {
      if (feedbackHandler!=NULL) feedbackHandler->onPressed(false);
      BIT_CLEAR(state,STATE_BUTTON);
    }
  }
  
  if (abs(CENTER_VALUE - x) > abs(CENTER_VALUE - y)) {// decide which axis has prio
    // handle horiz
    if ((x < CENTER_VALUE - VALUE_THRESHOLD)) {
      // left
      if (!BIT_CHECK(state,STATE_LEFT)) {
        BIT_SET(state,STATE_LEFT);
        if (feedbackHandler!=NULL) feedbackHandler->onLeft(true);
      }
    } else if ((x > CENTER_VALUE + VALUE_THRESHOLD)) {
      // right
      if (!BIT_CHECK(state,STATE_RIGHT)) {
        BIT_SET(state,STATE_RIGHT);
        if (feedbackHandler!=NULL) feedbackHandler->onRight(true);
      }
    } else {
      // none
      if (BIT_CHECK(state,STATE_LEFT)) {
        if (feedbackHandler!=NULL) feedbackHandler->onLeft(false);
        BIT_CLEAR(state,STATE_LEFT);
      }
      if (BIT_CHECK(state,STATE_RIGHT)) {
        if (feedbackHandler!=NULL) feedbackHandler->onRight(false);
        BIT_CLEAR(state,STATE_RIGHT);
      }
    }
  } else {
    // handle vert
    if ((y < CENTER_VALUE - VALUE_THRESHOLD)) {
      // down
      if (!BIT_CHECK(state,STATE_UP)) {
        BIT_SET(state,STATE_UP);
        if (feedbackHandler!=NULL) feedbackHandler->onUp(true);
      }
    } else if ((y > CENTER_VALUE + VALUE_THRESHOLD)) {
      // up
      if (!BIT_CHECK(state,STATE_DOWN)) {
        BIT_SET(state,STATE_DOWN);
        if (feedbackHandler!=NULL) feedbackHandler->onDown(true);
      }
    } else {

      // none
      if (BIT_CHECK(state,STATE_UP)) {
        if (feedbackHandler!=NULL) feedbackHandler->onUp(false);
        BIT_CLEAR(state,STATE_UP);
      }
      if (BIT_CHECK(state,STATE_DOWN)) {
        if (feedbackHandler!=NULL) feedbackHandler->onDown(false);
        BIT_CLEAR(state,STATE_DOWN);
      }
    }
  }
  
}

