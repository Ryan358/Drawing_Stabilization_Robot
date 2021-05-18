#include <Servo.h> 
 
Servo servo;  
 
// Control and feedback pins
int servoPin = 9;
int feedbackPin = A0;
 
// Calibration values
int minDegrees;
int maxDegrees;
int minFeedback;
int maxFeedback;
int tolerance = 2; // max feedback measurement error
int pos;
 
/*
  This function establishes the feedback values for 2 positions of the servo.
  With this information, we can interpolate feedback values for intermediate positions
*/
void calibrate(Servo servo, int analogPin, int minPos, int maxPos)
{
  // Move to the minimum position and record the feedback value
  servo.write(minPos);
  minDegrees = minPos;
  delay(2000); // make sure it has time to get there and settle
  minFeedback = analogRead(analogPin);
  
  // Move to the maximum position and record the feedback value
  servo.write(maxPos);
  maxDegrees = maxPos;
  delay(2000); // make sure it has time to get there and settle
  maxFeedback = analogRead(analogPin);
}


 
 
void setup() 
{ 
  servo.attach(servoPin); 
  
  calibrate(servo, feedbackPin, 0, 180);  // calibrate for the 20-160 degree range
} 
 
void loop()
{
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    int angle = map(analogRead(feedbackPin), minFeedback, maxFeedback, minDegrees, maxDegrees);
    Serial.print(angle); Serial.print("\t");
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    int angle = map(analogRead(feedbackPin), minFeedback, maxFeedback, minDegrees, maxDegrees);
    Serial.print(angle); Serial.print("\t");
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  
}
