"""This code MUST be named main.py. Otherwise, it will not run by default on the Pico.
This code is meant to be flashed using Thonny or your preferred editor
onto the Pico/microcontroller to get the position of the servos.
It does not actually actively read the positions. Instead, it defines the get_pos function,
and then waits. No code is run until the setup/damping code sends the get_pos function over the REPL
through serial communication. However, get_pos can be run independently to check
that the Pico is working and reading the position properly."""

from machine import Pin, ADC
from time import sleep

# creating the analog input objects
servo1pos = ADC(26)
servo2pos = ADC(27)


def get_pos():
    """This function gets the position of the servos by reading the two analog inputs,
    and returns the position as a two-entry list. It also prints the position for serial communication."""
    pos = [servo1pos.read_u16(), servo2pos.read_u16()]  # positions returned in integer form.
    # This print line is necessary for the serial communication.
    print(pos)
    # The return line is used for running the function during testing. Suggested to keep even after deployment.
    return pos


def main():
    """This code is just a simple way to check the function's operation."""
    print("Reading Position...")
    pos = get_pos()
    sleep(0.5)
    print(f"Servo 1 is at {pos[0]} and Servo 2 is at {pos[1]}")


if __name__ == "__main__":
    main()
