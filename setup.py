"""This code contains all the setup information for the servos and accelerometer. It also
contains the calibration function which is called by the main damping code. This module is mainly imported,
but can be run independently to calibrate the servos whenever necessary. """

# from gpiozero import Device, Servo
# This is the default import statement used for deployment. The only essential import is Servo.

# from gpiozero.pins.pigpio import PiGPIOFactory
# Device.pin_factory = PiGPIOFactory()

# This PiGPIO pin factory forces the pins to use the PiGPIO daemon to control the pins.
# This should reduce servo jitter and allow more precise PWM signals. If this gives you issues, remove
# the pin factory import and assignment and allow the code to just use its default settings, which may not use PWM well.


# The following imports and pin factory assignments are used to testing on a PC with no GPIO Pins.
# For deployment, use the above import/pin factory.
from gpiozero import Device, Servo
from gpiozero.pins.mock import MockFactory, MockPWMPin

from time import sleep
from sender import Sender
import json
import board
import adafruit_mma8451

# This line forces the code to use fake pins for testing. Remove when testing on an actual circuit.
Device.pin_factory = MockFactory(pin_class=MockPWMPin)

# For more info/troubleshooting on the pin factories and servo class,
# check the docs at https://gpiozero.readthedocs.io/en/stable/index.html

# declare servo pins, and initialize the accelerometer. This code always runs when imported.
# change these servo pins to whatever is going to be used.
servo1 = Servo(9)
servo2 = Servo(10)
i2c = board.I2C()
sensor = adafruit_mma8451.MMA8451(i2c)


def calibrate():
    """Calibrates the servo and provides voltage values at max and min positions. It does this by
    sending the get_pos command to the Pico over serial communication, and then stores these in a
    variable called cur_pos. This is then """
    port = 'COM8'  # replace this with the correct port. This initializes serial communication.
    s = Sender(port)
    # cur_pos will be a list of lists. The first entry is the minimum positions, and the second is the maximum.
    cur_pos = []
    servo1.min()
    servo2.min()
    sleep(2)  # allow time for servos to settle
    s.send('get_pos')
    cur_pos.append(json.loads(s.receive()))
    min_pos = cur_pos[0]
    sleep(1)
    servo1.max()
    servo2.max()
    sleep(2)  # allow time for servos to settle
    s.send('get_pos')
    s.receive()
    cur_pos.append(json.loads(s.receive()))
    max_pos = cur_pos[1]
    s.close()

    # this saves the current positions (min and max) as a json file that is used as a reference.
    with open('bounds.json', 'w') as f:
        json.dump(cur_pos, f)

    # The return statement exists because the calibration file will be called by the main code if no json file exists.
    return min_pos, max_pos


def main():
    print("Running Calibration...")
    calibrate()
    print("Calibrated!")


if __name__ == "__main__":
    main()
