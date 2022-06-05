   #include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

Servo servo1;
Servo servo2;

// Control and feedback pins
int servoPin1 = 9;
int servoPin2 = 10;
int feedbackPin1 = A1;
int feedbackPin2 = A2;

// Calibration values
int minDegrees;
int maxDegrees;
int minFeedback;
int maxFeedback;
int tolerance = 2; // max feedback measurement error
int pos;

float x_accel;
float y_accel;

int getPos(int analogPin)
{
  return map(analogRead(analogPin), minFeedback, maxFeedback, minDegrees, maxDegrees);
}


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

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  calibrate(servo1, feedbackPin1, 0, 180);  // calibrate for the 20-160 degree range
  calibrate(servo2, feedbackPin2, 0, 180);  // calibrate for the 20-160 degree range

  servo1.detach();
  servo2.detach();
}

void loop() {
  sensors_event_t event;
  mma.getEvent(&event);

  int pos1 = getPos(feedbackPin1);
  int pos2 = getPos(feedbackPin2);

  x_accel = (float)event.acceleration.x;
  y_accel = (float)event.acceleration.y;

  x_accel = abs(x_accel);
  y_accel = abs(y_accel);

  if (x_accel > 2 || y_accel > 2) {
    int pos1 = getPos(feedbackPin1);
    int pos2 = getPos(feedbackPin2);

    servo1.write(pos1);
    servo2.write(pos2);

    servo1.attach(servoPin1);
    servo2.attach(servoPin2);

    delay(10);

    servo1.detach();
    servo2.detach();

  }
    delay(10);
}
