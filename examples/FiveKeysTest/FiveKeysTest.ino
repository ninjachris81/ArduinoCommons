#include <FiveKeysHandler.h>
#include "KeyHandler.h"

KeyHandler kh;
FiveKeysHandler fkh(A0);

void setup() {
  Serial.begin(115200);          // Set Serial Monitor lower right to 115200
  Serial.println("Testing Analog Buttons ");
  fkh.init(&kh);
}

void loop() {
  fkh.update();
}
