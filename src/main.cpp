#include <Arduino.h>
#include "ps5Controller.h"
#include "ESP32_Servo.h"

Servo myservo;

int servopin[1] = {18};

void setup() {
  Serial.begin(115200);
  ps5.begin("A0:FA:9C:2B:D4:DD");
  Serial.println("Ready.");
  for(int i = 0; i < sizeof(servopin) / sizeof(int); i++)
  {
    if(myservo.attach(servopin[i]) == 0)
    {
      Serial.printf("pin:%d サーボの接続失敗\n", servopin[i]);
    }
  }
}

void loop() {
  if(ps5.isConnected())
  {
    Serial.printf("left:%d right:%d\n",ps5.LStickY(),ps5.RStickY());
    //PropellerPower(ps5.LStickY(), ps5.RStickY());
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

void ServoPower(int degree)
{
  if (degree >= 0 && degree <= 180)
  {
    myservo.write(degree);
  }
  else
  {
    Serial.printf("サーボ角度指定エラー:%d\n", degree);
  }
}