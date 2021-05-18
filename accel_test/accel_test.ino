#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

int x_accel[100];
int y_accel[100];
int i;
void setup(){
    Serial.begin(9600);
  
    Serial.println("Adafruit MMA8451 test!");
  

    if (! mma.begin()) {
        Serial.println("Couldnt start");
    while (1);
    }
    Serial.println("MMA8451 found!");
  
    mma.setRange(MMA8451_RANGE_2_G);
  
    Serial.print("Range = "); Serial.print(2 << mma.getRange());  
    Serial.println("G");
    for(i=0;i=99; i+=1){
        sensors_event_t event; 
        mma.getEvent(&event);
        x_accel[i] = event.acceleration.x;
        Serial.print(event.acceleration.x);
        delay(300);
    }
    

}

void loop(){


}