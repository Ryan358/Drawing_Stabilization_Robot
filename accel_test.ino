#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Servo.h> 
 
Servo servo; 

Adafruit_MMA8451 mma = Adafruit_MMA8451();

int i;
int angle = 0;
float x;


void setup(){
    Serial.begin(9600);
    servo.attach(9);
    Serial.println("Adafruit MMA8451 test!");
  

    if (! mma.begin()) {
        Serial.println("Couldnt start");
    while (1);
    }
    Serial.println("MMA8451 found!");
  
    mma.setRange(MMA8451_RANGE_2_G);
  
    Serial.print("Range = "); Serial.print(2 << mma.getRange());  
    Serial.println("G");
    
    sensors_event_t event;
    mma.getEvent(&event);
    Serial.print(event.acceleration.x); Serial.print("\t"); 
    Serial.print(event.acceleration.y); Serial.print("\t");
    Serial.print(event.acceleration.z); Serial.print("\t");

    Serial.println();

    

}

void loop(){
  
    sensors_event_t event;
    mma.getEvent(&event);
    //Serial.print(event.acceleration.x); Serial.print("\t"); 
    //Serial.print(event.acceleration.y); Serial.print("\t");
    //Serial.print(event.acceleration.z); Serial.print("\t");

    Serial.println();
    
    delay(50);
    x = (float)event.acceleration.x;
    if (x > 2.5){
        angle += 10;
        servo.write(angle);
        delay(50);
    }
    Serial.print(x);
    delay(100);

}
