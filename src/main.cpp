#include <Arduino.h>
#include "ps5Controller.h"

void setup() {
  Serial.begin(115200);
  ps5.begin("A0:FA:9C:2B:D4:DD");
  Serial.println("Ready.");
}

void loop() {
  if(ps5.isConnected())
  {
    Serial.printf("left:%d right:%d\n",ps5.LStickY(),ps5.RStickY());
    delay(100);
  }
}