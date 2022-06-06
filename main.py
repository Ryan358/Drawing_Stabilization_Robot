from machine import Pin, ADC
from time import sleep

# creating the analog input objects
servo1pos = ADC(26)
servo2pos = ADC(27)


def getPos():
    pos = [300, 400]
    # pos = [servo1pos.read_u16(), servo2pos.read_u16()]
    print(pos)
    return pos


def main():
    print("Reading Position...")
    pos = getPos()
    sleep(0.5)
    print(f"Servo 1 is at {pos[0]} and Servo 2 is at {pos[1]}")


if __name__ == "__main__":
    main()
