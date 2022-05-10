# Line-Follower

A line follower robot was made using Arduino UNO. 
Components:
5-Channel IR Sensor Module
Arduino UNO 
3S 11.1V Lithium Polymer Battery
L293D Motor Driver
2x BO Motors
2-wheeled Plastic Chassis
SPST
Bunch of Jumper Wires

Code is based only on Proportional Control system approach, which takes a weighted mean value from the 5-sensors.
Robot gave considerable results with just the proportional term without derivative and integrative term.

We have varied the time in the delay functions, one could modify the code easily by applying the same logic to change the motor speed.
