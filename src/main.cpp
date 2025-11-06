#include "Arduino.h"
#include "PS4Controller.h"
#include "ESP32_Servo.h"

int motorPin[8] = {17, 16, 22, 0, 25, 26, 15, 14};


void setup() 
{
  Serial.begin(115200);
  PS4.begin("3C:8A:1F:91:66:86");
  Serial.println("PS4 Ready.");
  for(int i = 0; i < sizeof(motorPin) / sizeof(int); i++)
  {
    ledcSetup(i, 12800, 8);
    ledcAttachPin(motorPin[i], i);
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

void setArmPower(int power)
{
  if (power > 20)
  {
    ledcWrite(4, power);
    ledcWrite(5, 0);
  }
  else if (power < -20)
  {
    ledcWrite(4, 0);
    ledcWrite(5, abs(power));
  }
  else
  {
    ledcWrite(4, 0);
    ledcWrite(5, 0);
  }
}

void loop()
{
  if(PS4.isConnected())
  {
    setPropellerPower(PS4.LStickY(), PS4.RStickY());
    setArmPower(PS4.R2Value() - PS4.L2Value());
    delay(100);
  }
  else
  {
    Serial.printf("コントローラーが接続されていません\n");
    delay(1000);
  }
}
