#include <Servo.h>            //Servo library
 
Servo servo1;        //initialize a servo object for the connected servo  
Servo servo2;
                
int angle = 0;

void setup() 
{ 
  servo1.attach(9);      // attach the signal pin of servo to pin9 of arduino
  servo2.attach(10);
} 

int start_angle1 = 50;
int start_angle2 = 180;

int end_angle1 = 105;
int end_angle2 = 85;

int max_interval = start_angle2 - end_angle2;
int interval1 = start_angle1 - end_angle1;
int scaler = interval1/max_interval;


void loop()
{
    int i;
    int j;

    servo1.write(start_angle1);
    servo2.write(start_angle2);
    
    delay(1000);

    for(i = 0; i <= max_interval; i+=1)
    {
        j = i*0.58;
        servo2.write(start_angle2 - i);
        servo1.write(start_angle1 + j);
       
        
        delay(50);
    }

    delay(1000);

}
