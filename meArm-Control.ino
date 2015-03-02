/*============================================================================
  meArm Software by Scott Pierce - sales@buildacnc.com - www.buildacnc.com
  
  The following is heavily based on but a complete rewrite of code found here:
  http://www.instructables.com/id/MeArm-software/

  Pin 5  = Height Servo
  Pin 9  = Gripper Servo
  Pin 10 = Extension Servo
  Pin 11 = Pivot Servo
  
==============================================================================*/

#include <Servo.h>

#define NUM_SERVOS 4
#define DELAY_TIME 5

byte servoPins[] = {5, 9, 10, 11};

struct ServoStruct
{
  Servo servo;
  byte pin;
  byte currentPosition;
  byte lastPosition;
  byte minPosition;
  byte maxPosition;
  byte centerPosition;
  byte homePosition;
  boolean reverse;
  byte idleCycles;
};//struct

ServoStruct Servos[NUM_SERVOS];

void setup()
{
  Serial.begin(57600);
  Serial.println("Initializing Servos");
  
  for (int i = 0; i < NUM_SERVOS; i++)
  {
    Servos[i].pin = servoPins[i];
    Servos[i].minPosition = 0;
    Servos[i].maxPosition = 179;
    Servos[i].centerPosition = ((Servos[i].maxPosition - Servos[i].minPosition)/2)+Servos[i].minPosition;
    Servos[i].homePosition = Servos[i].centerPosition;
    Servos[i].lastPosition = Servos[i].homePosition;
    Servos[i].currentPosition = Servos[i].lastPosition;
    Servos[i].reverse = true;
    Servos[i].idleCycles = 0;
    Servos[i].servo.attach(servoPins[i]);    
    Servos[i].servo.write(Servos[i].homePosition);
    
  }//for
  
  Servos[3].reverse = false;
  
}//setup

void loop()
{
  for (int i = 0; i < NUM_SERVOS; i++)
  {
    Servos[i].lastPosition = Servos[i].currentPosition;
    int potVal = analogRead(i);
    
    if(potVal > 612)
    {
      if(Servos[i].reverse)
      {
        if(Servos[i].currentPosition > Servos[i].minPosition)
          Servos[i].currentPosition--;
      }//if
        
      else
      {
        if(Servos[i].currentPosition < Servos[i].maxPosition)
          Servos[i].currentPosition++;
      }//else
    }//if
    
    else if (potVal < 412)
    {
      if(Servos[i].reverse)
      {
        if(Servos[i].currentPosition < Servos[i].maxPosition)
          Servos[i].currentPosition++;
      }//if
      
      else
      {
        if(Servos[i].currentPosition > Servos[i].minPosition)
          Servos[i].currentPosition--;
      }//else
    }//else if
    
    if(Servos[i].currentPosition != Servos[i].lastPosition)
      Servos[i].servo.write(Servos[i].currentPosition);    
    
    delay(DELAY_TIME);
   } //for  
}//loop
