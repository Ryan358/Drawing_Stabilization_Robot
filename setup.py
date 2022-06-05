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

# This line forces the code to use fake pins for testing. Remove when testing on an actual circuit.
Device.pin_factory = MockFactory(pin_class=MockPWMPin)

# For more info/troubleshooting on the pin factories and servo class,
# check the docs at https://gpiozero.readthedocs.io/en/stable/index.html

servo1 = Servo(9)
servo2 = Servo(10)


def calibrate():
    """Calibrates the servo and provides voltage values at max and min positions"""
    servo1.min()
    servo2.min()
    pass


def main():
    print("Running Calibration...")
    calibrate()
    print("Calibrated!")


if __name__ == "__main__":
    main()
