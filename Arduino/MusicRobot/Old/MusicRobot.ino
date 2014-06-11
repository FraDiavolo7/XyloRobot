#include "Makeblock.h"
#include <SoftwareSerial.h>
#include <Wire.h>

MeStepperMotor stepper(PORT_1,0x1);
MeUltrasonicSensor ultraSensor(PORT_3);
MeDCMotor kicker(M1);
MeRGBLed led(PORT_4,DEV1);
MeLimitSwitch sw(PORT_4,DEV2);

int targetIndex = -1;
int currentIndex = -1;
int value;
long startPosition = 0;

unsigned int knockFlag = false;
unsigned int onestep = 79;
int prevIndex=0;
int lastNum = 0;

void initStepper(){
  stepper.begin(); // initialize stepper driver.
  stepper.setMicroStep(STP_HALF);
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(500);
  stepper.run(); 
  // output pulse
  stepper.moveTo(-10000);
  while(sw.touched());
  stepper.stop();
  stepper.setCurrentPosition(0);
  startPosition = -50;//stepper.currentPosition();
  stepper.setMaxSpeed(20000);
  stepper.setAcceleration(10000);
  stepper.run();
  stepper.moveTo(50);
  while(stepper.currentPosition()!=50);
  Serial.println("Stepper Begin");
}

void setup()
{
  initStepper();
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(7,HIGH);
  analogWrite(6,0);
  pinMode(6,INPUT);
  led.setNumber(31);
}

int ledFlag = true;
void loop()
{
    if(Serial.available())
    {
    char temp = Serial.read(); 
    if(temp< 0x12){
       targetIndex = temp;
       knockFlag = true;
    }
     if(targetIndex!=prevIndex){
     moveStepper();
     prevIndex = targetIndex;  
   }
  }
  else
  {
    value = ultraSensor.distanceCm();
    if(value <70)
    {
    if(value <10)
    {
      targetIndex = 1;
    }
      else if(value <20)
      {
      targetIndex = 2;
      }
      else if(value <30)
      {
      targetIndex = 3;
      }
      else if(value <40)
      {
      targetIndex = 4;
      }
      else if(value <50)
      {
      targetIndex = 5;
      }
      else if(value <60)
      {
      targetIndex = 6;
      }
      else if(value <70)
      {
      targetIndex = 7;
      }
      else
      { 
      targetIndex = 16;
      }
//      Serial.printf("%d,%d\n",value,targetIndex);
      if(targetIndex!=prevIndex)
      {
       if(targetIndex<16){
         knockFlag = true;
         moveStepper();
//         moveLight();
       }
       prevIndex = targetIndex;  
      }
    } 
  }
   indicators(targetIndex*2,20,30,40);
   delay(150);
   checkStepperPosition();
   delay(50);
}


void kickoff()
{
 
  knockFlag = false; 
  Serial.println("kick"); 
  pinMode(6,OUTPUT);
  analogWrite(6,100);
  delay(50);
  analogWrite(6,0);
  pinMode(6,INPUT);
}

void moveStepper(){
  if(targetIndex >=  0)
  {
    int stepPos = startPosition+targetIndex*onestep;
//    Serial.printf("step move to %d\n",stepPos);
    stepper.moveTo(stepPos);
  }
}

void checkStepperPosition()
{
  int steptogo = abs(stepper.currentPosition()-stepper.targetPosition());
    if(steptogo==0 && knockFlag){
      kickoff();
    }
}

//void moveLight(){
//  int offset = currentIndex - targetIndex;
//  if(offset!=0){
//   ledOn(currentIndex*1.8);
//   currentIndex+=(offset>0) ?( -1 ):( 1);
//   delay(50);
//  }
//  else
//  {
//   delay(50); 
//  }
//}

void indicators(byte count,byte r,byte g,byte b){
  byte inSpeed = 10;
  if(lastNum <= count){
      for(int x = lastNum; x <= count; ++x){
          led.setColorAt(x,r,g,b);
          led.show();
          delay(inSpeed);
      }
    }
    else{
      for(int x = lastNum; x > count; --x){
          led.setColorAt(x,0,0,0);
          led.show();
          delay(inSpeed);
      }
    }
    lastNum = count; 
}
//void ledOn(int lednum)
//{
//  int red;
//  for(int i=0;i<led.getNumber();i++){
//    red = max(0,50-abs(i-lednum)*scaleFade);
//    led.setColorAt(i, red,red==0?0:20*red/50,red==0?0:10*red/50);
//  }
//  led.show();
//}
