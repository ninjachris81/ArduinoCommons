#ifndef joystick_handler_h
#define joystick_handler_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


#define CENTER_VALUE 518
#define VALUE_THRESHOLD 80

#define STATE_LEFT 1
#define STATE_RIGHT 2
#define STATE_UP 3
#define STATE_DOWN 4
#define STATE_BUTTON 5

#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

class JoystickHandler {
public:
  JoystickHandler(uint8_t pinX, uint8_t pinY, uint8_t pinBtn);

  class JoystickFeedbackHandler {
    public:
    virtual void onLeft(bool isDown) = 0;
    virtual void onRight(bool isDown) = 0;
    virtual void onUp(bool isDown) = 0;
    virtual void onDown(bool isDown) = 0;
    virtual void onPressed(bool isDown) = 0;
  };
  
  void update();
  
  void setFeedbackHandler(JoystickFeedbackHandler *feedbackHandler);

private:
  uint8_t pinX;
  uint8_t pinY;
  uint8_t pinBtn;
  
  JoystickFeedbackHandler *feedbackHandler;
  uint8_t state = 0;  
};



#endif
