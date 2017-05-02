#include "KeyHandler.h"

KeyHandler::KeyHandler() {
}

void KeyHandler::onLeft(bool isDown) {
  Serial.print("onLeft ");
  Serial.println(isDown, DEC);
}

void KeyHandler::onRight(bool isDown) {
  Serial.print("onRight ");
  Serial.println(isDown, DEC);
}

void KeyHandler::onUp(bool isDown) {
  Serial.print("onUp ");
  Serial.println(isDown, DEC);
}

void KeyHandler::onDown(bool isDown) {
  Serial.print("onDown ");
  Serial.println(isDown, DEC);
}

void KeyHandler::onPressed(bool isDown) {
  Serial.print("onPressed ");
  Serial.println(isDown, DEC);
}

