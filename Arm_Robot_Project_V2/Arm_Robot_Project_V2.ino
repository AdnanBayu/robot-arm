#include "Wire.h"
#include <MPU6050_light.h>
#include <Servo.h>

MPU6050 mpu(Wire);  //SCL A5 & SDA A4
unsigned long timer = 0;

Servo servo1; //roll
Servo servo2; //pitch
Servo servo3; //yaw
Servo servo4; //claw

void setup() {
  Serial.begin(9600);
  servo1.attach(3); //roll
  servo2.attach(10); //pitch
  servo3.attach(6); //yaw
  servo4.attach(9); //claw
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status == 0) {}  // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  if ((millis() - timer) > 10) {  // print data every 10ms
    Serial.println("");
    Serial.print("Pitch : ");
    Serial.print(mpu.getAngleX());
    Serial.print("\tRoll : ");
    Serial.print(mpu.getAngleY());
    Serial.print("\tYaw : ");
    Serial.print(mpu.getAngleZ());
    timer = millis();
  }

  // servoRoll(mpu.getAngleY());
  // servoPitch(mpu.getAngleX());
  // servoYaw(mpu.getAngleZ());
  delay(10);
}

void servoRoll(float a) {
  float aMax = a+40;
  float aMin = a-40;
  if(a>aMax){
    a=aMax;
  }
  else if(a<aMin){
    a=aMin;
  }
  float sudutRoll = map(a, aMin, aMax, 0, 65);  //akselerasi x
  servo1.write(sudutRoll);
  Serial.print("\tSudut Roll : ");
  Serial.print(sudutRoll);
}

void servoPitch(float b) {
  float bMax = b+40;
  float bMin = b-40;
  if(b>bMax){
    b=bMax;
  }
  else if(b<bMin){
    b=bMin;
  }
  float sudutPitch = map(b, bMin, bMin, 100, 180);  //akselerasi y
  servo2.write(sudutPitch);
  Serial.print("\tSudut Pitch : ");
  Serial.print(sudutPitch);
}

void servoYaw(float c) {
  float cMax = c+40;
  float cMin = c-40;
  if(c>cMax){
    c=cMax;
  }
  else if(c<cMin){
    c=cMin;
  }
  float sudutYaw = map(c, cMin, cMax, 0, 180);
  servo3.write(sudutYaw);
  Serial.print("\tSudut Yaw : ");
  Serial.print(sudutYaw);
}

// void servoClaw(float d){
//   float sudutClaw = map(d, 0, 1023, 0, 180);
//   servo4.write(sudutClaw);
// }