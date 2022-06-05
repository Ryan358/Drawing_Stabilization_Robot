from machine import Pin, ADC
from time import sleep

# creating the analog input objects
servo1 = ADC(26)
servo2 = ADC(27)


def getPos(servo):
    servo.read_u16()


def main():
    while True:
        getPos(servo1)
        getPos(servo2)
        sleep(0.01)


if __name__ == "__main__":
    main()
