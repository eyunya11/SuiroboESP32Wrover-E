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

void PropellerPower(int left, int right)
{
  if (left > 20)
  {
    ledcWrite(0, left);
    ledcWrite(1, 0);
  }
  else if (left < -20)
  {
    ledcWrite(0, 0);
    ledcWrite(1, abs(left));
  }
  else
  {
    ledcWrite(0, 0);
    ledcWrite(1, 0);
  }
  
  if (right > 20)
  {
    ledcWrite(2, right);
    ledcWrite(3, 0);
  }
  else if (right < -20)
  {
    ledcWrite(2, 0);
    ledcWrite(3, abs(right));
  }
  else
  {
    ledcWrite(2, 0);
    ledcWrite(3, 0);
  }
}