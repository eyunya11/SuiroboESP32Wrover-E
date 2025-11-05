#include "Arduino.h"
#include "PS4Controller.h"
#include "ESP32_Servo.h"

int motorPin[4] = {17, 16, 22, 0};

void setup() {
  Serial.begin(115200);
  PS4.begin("A0:FA:9C:2B:D4:DD");
  Serial.println("PS4 Ready.");
  for(int i = 0; i < sizeof(motorPin) / sizeof(int); i++)
  {
    ledcSetup(i, 12800, 8);
    ledcAttachPin(motorPin[i], i);
  }
}

void loop() {
  if(PS4.isConnected())
  {
    Serial.printf("left:%d right:%d\n",PS4.LStickY(),PS4.RStickY());
    //PropellerPower(PS4.LStickY(), PS4.RStickY());
    delay(100);
  }
  else
  {
    Serial.printf("コントローラーが接続されていません\n");
    delay(500);
  }
}

void setPropellerPower(int left, int right)
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