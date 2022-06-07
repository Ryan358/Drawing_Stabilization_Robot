from sender import Sender
from time import sleep
import json
from setup import calibrate, servo1, servo2, sensor
from numpy import interp
import os.path

threshold = 2


def main():
    """This function contains the code to damp the servos."""

    # This checks for the bounds.json file generated by the calibration module.
    # If it is detected, then no need to calibrate. If not, then the calibration runs.

    if os.path.exists('bounds.json'):
        with open('bounds.json') as f:
            bounds = json.load(f)
            min_bounds = bounds[0]
            max_bounds = bounds[1]
    else:
        min_bounds, max_bounds = calibrate()

    servo1.detach()
    servo2.detach()
    # This opens the port for the serial communication.
    port = 'COM8'  # replace this with the correct port
    s = Sender(port)
    while True:
        x, y, z = sensor.acceleration
        if abs(x) > threshold or abs(y) > threshold:
            s.send('get_pos()')
            s.receive()
            cur_pos = json.loads(s.receive())
            # Interpolate the current positions to map it to the range of [-1,1],
            # which is accepted by the servo command.
            cur_pos_1 = interp(cur_pos[0], [min_bounds[0], max_bounds[0]], [-1, 1])
            cur_pos_2 = interp(cur_pos[1], [min_bounds[1], max_bounds[1]], [-1, 1])
            servo1.value(cur_pos_1)
            servo2.value(cur_pos_2)

            sleep(0.01)

            servo1.detach()
            servo2.detach()

        sleep(0.01)


if __name__ == "__main__":
    main()
