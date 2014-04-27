
#include "Makeblock.h"
#include <SoftwareSerial.h>
#include <Wire.h>

MeStepperMotor stepper (PORT_1, 0x1);
MeUltrasonicSensor ultraSensor (PORT_3);
MeDCMotor kicker (M1);
MeRGBLed led (PORT_4, DEV1);
MeLimitSwitch sw (PORT_4, DEV2);

int targetIndex = -1;
int currentIndex = -1;
int value;
long StartPosition = 0;

unsigned int KnockFlag = false;
unsigned int OneStep = 79;
int PrevIndex = 0;
int TargetIndex = 0;

int TimingReadNote = 150;   // Fixed time for the readNote function. 
int TimingMoveHammer = 150; // Fixed time for the moveHammer function. 
int TimingKnock = 150;      // Fixed time for the knock function. 
int TempoStep = 10;         // Time needed to move from one step to another.

void initStepper ()
{
    stepper.begin (); // initialize stepper driver.
    stepper.setMicroStep (STP_HALF);
    stepper.setMaxSpeed (500);
    stepper.setAcceleration (500);
    stepper.run ();
    // output pulse
    stepper.moveTo ( -10000);
    while (sw.touched ())
        ;
        
    stepper.stop ();
    stepper.setCurrentPosition (0);
    StartPosition = -50; //stepper.currentPosition();
    stepper.setMaxSpeed (20000);
    stepper.setAcceleration (10000);
    stepper.run ();
    stepper.moveTo (50);
    while (stepper.currentPosition () != 50)
        ;
    Serial.println ("Stepper Begin");
}

void setup ()
{
    initStepper ();
    Serial.begin (9600);
    pinMode (7, OUTPUT);
    pinMode (6, OUTPUT);
    digitalWrite (7, HIGH);
    analogWrite (6, 0);
    pinMode (6, INPUT);
    led.setNumber (31);
}

/**
 * This function is responsible of the reading of the Note to play
 * This function always take the same time to execute.
**/
int readNote ()
{
    int IndexNote = 0;
    
    if (Serial.available ())
    {
        char temp = Serial.read ();
        if (temp < 0x12)
        {
            IndexNote = temp;
            KnockFlag = true;
        }
    }
    else
    {
        value = ultraSensor.distanceCm ();
        if (value < 70)
        {
            if (value < 10)
            {
                IndexNote = 1;
            }
            else if (value < 20)
            {
                IndexNote = 2;
            }
            else if (value < 30)
            {
                IndexNote = 3;
            }
            else if (value < 40)
            {
                IndexNote = 4;
            }
            else if (value < 50)
            {
                IndexNote = 5;
            }
            else if (value < 60)
            {
                IndexNote = 6;
            }
            else if (value < 70)
            {
                IndexNote = 7;
            }
            else
            {
                IndexNote = 16;
            }

//            Serial.printf ("%d,%d\n", value, IndexNote);
        }

        if (IndexNote < 16)
        {
            KnockFlag = true;
        }
    }

    return IndexNote;
}

/**
 * This function is responsible of the moving of the hammer.
 * This function always take the same time to execute.
**/
void moveHammer ()
{
    int Tempo = TimingMoveHammer;
    
    if ( (TargetIndex >= 0) && (TargetIndex != PrevIndex) )
    {
        int StepPos = StartPosition + TargetIndex * OneStep;
        stepper.moveTo (StepPos);
        Tempo -= abs (TargetIndex - PrevIndex) * TempoStep;
        PrevIndex = TargetIndex;
    }
    
    delayMicroseconds (Tempo);
}

/**
 * This is a copy of the kickoff function
 * This function is commanding the Hammer to knock
**/
void knock ()
{
    if ( KnockFlag )
    {
        KnockFlag = false;
        Serial.println ("kick");
        pinMode (6, OUTPUT);
        analogWrite (6, 100);
        delay (50);
        analogWrite (6, 0);
        pinMode (6, INPUT);
    }
    else
    {
        delayMicroseconds (TimingKnock);
    }
}

int ledFlag = true;
void loop ()
{
    int TargetIndex = readNote ();
    
    moveHammer ();

    knock ();
}
