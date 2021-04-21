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
    servo1.write(angle);
    servo2.write(angle);
}