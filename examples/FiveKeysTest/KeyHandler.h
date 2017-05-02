#ifndef KEYHANDLER
#define KEYHANDLER

#include <FiveKeysHandler.h>

class KeyHandler : public FiveKeysHandler::FKFeedbackHandler {
public:
  KeyHandler();
    
  void onLeft(bool isDown);
  void onRight(bool isDown);
  void onUp(bool isDown);
  void onDown(bool isDown);
  void onPressed(bool isDown);

  
};

#endif    // KEYHANDLER
