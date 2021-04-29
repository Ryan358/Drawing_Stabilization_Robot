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
    servo1.write(50);
    servo2.write(180);
    
    delay(1000);

    servo1.write(105);
    servo2.write(90);

    delay(1000);

}
