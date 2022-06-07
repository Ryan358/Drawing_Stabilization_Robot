# Drawing Stabilization Robot
 This robot is designed to stabilize hand tremors in people with motor function issues. For hardware testing: I suggest testing Main first to get the analog inputs settled, then test setup to ensure that you can move and calibrate servos properly. Then you can test damping. 

# Code
The code is split into three separate modules; main.py, damping.py, and setup.py. Main.py controls the Pico, setup.py
is used to initialize the servos and sensors, as well as to calibrate the servos, and damping.py runs the main logic loop
for servo control and sensor data checks. 

### **Main**: 
This code **MUST** be named main.py, or it will not run by default on a Pico. This code is meant to be flashed onto a Pico or microcontroller running Micropython. It waits to receive serial commands
from the host, and then prints out the current position of the analog feedback servos. For testing analog feedback, the servo
positions can be read by running the get_pos from Thonny or any editor that can access the REPL.

### **Setup**:
The setup module contains all the pin definitions for the servos, as well as the accelerometer initialization.
Any changes to wiring/setup of the servos or sensors is likely to need to be adjusted here. All of these are defined and
created upon import of the setup module into the main code. This module also contains the calibration function used to 
create the min/max bounds of the servo in integer or voltage form. This is necessary because servos only accept positions
from the range of [-1, 1], so the min and max bounds are needed for interpolation. Calibration can be done by simply running 
setup.py from the command line; or, if desired, can be run as part of the damping code. This will be performed if there is already no 
json file containing the bounds. 

### **Damping**:
This code uses the data from setup to check accelerometer data and control the servos accordingly. Using the initializations
from setup.py and the current positions provided by main.py, this code checks if hand movement exceeds a threshold of acceleration and momentarily stiffens the servos
if it does. 

For hardware testing: I suggest testing Main first to get the analog inputs settled, then test setup to ensure that you can move and calibrate servos properly. Then you can test damping. 
