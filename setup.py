# from gpiozero import Device, Servo
# This is the default import statement used for deployment. The only essential import is Servo.

# from gpiozero.pins.pigpio import PiGPIOFactory
# Device.pin_factory = PiGPIOFactory()

# This PiGPIO pin factory forces the pins to use the PiGPIO daemon to control the pins.
# This should reduce servo jitter and allow more precise PWM signals. If this gives you issues, remove
# the pin factory import and assignment and allow the code to just use its default settings, which may not use PWM well.


# The following imports and pin factory assignments are used to testing on a PC with no GPIO Pins.
# #For deployment, use the above import/pin factory.
from gpiozero import Device, Servo
from gpiozero.pins.mock import MockFactory, MockPWMPin

from time import sleep
from sender import Sender
import json

# This line forces the code to use fake pins for testing. Remove when testing on an actual circuit.
Device.pin_factory = MockFactory(pin_class=MockPWMPin)

# For more info/troubleshooting on the pin factories and servo class,
# check the docs at https://gpiozero.readthedocs.io/en/stable/index.html

servo1 = Servo(9)
servo2 = Servo(10)


def calibrate():
    """Calibrates the servo and provides voltage values at max and min positions"""
    port = 'COM8'  # replace this with the correct port
    s = Sender(port)
    servo1.min()
    servo2.min()
    sleep(2)  # allow time for servos to settle
    s.send('getPos()')
    curPos = json.loads(s.receive())
    minPos = curPos
    sleep(0.5)
    servo1.max()
    servo2.max()
    sleep(2)  # allow time for servos to settle
    s.send('getPos()')
    s.receive()
    curPos = json.loads(s.receive())
    maxPos = curPos
    s.close()
    return minPos, maxPos


def main():
    print("Running Calibration...")
    calibrate()
    print("Calibrated!")


if __name__ == "__main__":
    main()
