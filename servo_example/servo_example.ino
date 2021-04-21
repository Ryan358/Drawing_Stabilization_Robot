#include <Servo.h>            //Servo library
 
Servo servo1;        //initialize a servo object for the connected servo  
Servo servo2;
                
int angle = 0;

void setup() 
{ 
  servo1.attach(9);      // attach the signal pin of servo to pin9 of arduino
  servo2.attach(10);
} 

void loop()
{

    for(angle = 0; angle < 90; angle += 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    servo1.write(angle);                 //command to rotate the servo to the specified angle
    servo2.write(angle);
    delay(15);                       
  }

  for(angle = 90; angle <= 1; angle +- 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    servo1.write(angle);                 //command to rotate the servo to the specified angle
    servo2.write(angle);
    delay(15);                       
  }
}