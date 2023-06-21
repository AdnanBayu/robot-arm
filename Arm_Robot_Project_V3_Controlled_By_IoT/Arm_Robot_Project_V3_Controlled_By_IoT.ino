#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

char auth[] = "Yz0SWGMkVpKUlvn-SmsLigmpnNCwkbM1";
char ssid[] = "IndiHome";
char pass[] = "CikAs1946";

int servoPin1 = 2;  //yaw
int servoPin2 = 4;  //roll
int servoPin3 = 5;  //pitch

Servo servo1;   //yaw
Servo servo2;   //roll
Servo servo3;   //pitch

void setup()
{
  Serial.begin(115200);
  // Koneksi WiFi
  Blynk.begin(auth, ssid, pass);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
}

void loop(){
  Blynk.run();
}

BLYNK_WRITE(V2)     //yaw
{
  int servoPos1 = param.asInt();
  servo1.write(servoPos1);
}

BLYNK_WRITE(V4)     //roll
{
  int servoPos2 = param.asInt();
  servo2.write(servoPos2);
}

BLYNK_WRITE(V5)     //pitch
{
  int servoPos3 = param.asInt();
  servo3.write(servoPos3);
}