#include <Servo.h>
Servo myservo;
// Control and feedback pins
int servoPin = 9;
int feedbackPin = A0;
// Calibration values
int minDegrees;
int maxDegrees;
int minFeedback;
int maxFeedback;
int tolerance = 2; // max feedback measurement error
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
myservo.attach(servoPin);
calibrate(myservo, feedbackPin, 0, 180); // calibrate for the 20-160 degree range
}
void loop()
{
}
