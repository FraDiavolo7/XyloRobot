
/*************************************************************************
* File Name          : MusicRobot.ino
* Author             : Evan
* Updated            : Evan
* Version            : V2.0.0
* Date               : 6/5/2013
* Description        : 1 Step Motors
* License            : CC-BY-SA 3.0
* Copyright (C) 2011 Hulu Robot Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, 12,13); // 12-PUL, 13-DIR
int limitSW = 8;
int magnetDrc = 7;
int magnetPwm = 6;
int stepMotorEN = 11;

void initMotor()
{
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(15000);
  stepper.moveTo(-4000);
  while(!digitalRead(limitSW)) stepper.run(); 
  stepper.stop();
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(5000);//5000
}

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  pinMode(limitSW, INPUT);
  pinMode(magnetDrc, OUTPUT);
  pinMode(magnetPwm, OUTPUT);
  pinMode(stepMotorEN, OUTPUT);
  digitalWrite(stepMotorEN, HIGH);
  digitalWrite(magnetDrc, LOW);
  digitalWrite(magnetPwm, 0);
  initMotor();
  Serial.begin(9600);
  Serial.print("start:");Serial.println(digitalRead(limitSW));
}

unsigned int scale = 0;
unsigned char rxTemp = 0;
boolean receiveFlag = true;
boolean knockFlag = false;
// the loop routine runs over and over again forever:
void loop()
{
  if(Serial.available() && receiveFlag)
  {
    rxTemp = Serial.read();
    if(rxTemp < 0x12) //0 ~ 17 scale
    {
      scale = rxTemp * 223;
      stepper.moveTo(scale);
      receiveFlag = false;
      knockFlag = true;
    }
  }
  
  while ( stepper.currentPosition() != scale )
    stepper.run(); 
  
  if( stepper.currentPosition() == scale )
  {
    if(knockFlag) //knock
    {
      analogWrite(magnetPwm, 255);
      delay(50);
      analogWrite(magnetPwm, 0);
      Serial.write(1);
      knockFlag = false;
    }
    receiveFlag = true;
  }
}


