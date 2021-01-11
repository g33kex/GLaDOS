
This project consist of programming a _LEGO MINDSTORMS EV3_ robot to complete the **warehouse** challenge : grabbing balls in a box and moving them to a given destination. 

It is a challenge for our OS course at [Eurecom](https://www.eurecom.fr/). Here are our team members : 
* Florian Le Mouël
* Mathieu Champion
* Virgile Retault

## Description of the robot

![Picture of the robot](images/robot1.png)

The robot has active independant wheels and is controlled with a differential drive. A third passive wheel is used to stabilize it.  
Tacheometry and sensor fusion is used to determine its position at all time.

A large claw that's about the width of the cube is used to grab the balls and is mounted on a crane-like structure to raiser and lower it. 

![Picture of the claw](images/claw.png)

### Sensors

* Magnetic sensor (compass)
    - Used to compute the absolute rotation
* Gyroscope sensor
    - Used to measure the relative rotation, fused with the compass
* Ultrasonic sensor (distance sensor)
    - Used to measure the distance of the robot to objects to help with positioning
* Color sensor in the claw
    - Used to tell if a ball has been succesfully picked up or not

![Picture of the sensors](images/sensors.png)

### Actuators

* Two motors for the wheels
* One motor to open and close the claw 
* One motor to lower and raise the claw

![Picture of the motors](images/motors.png)

## Algorithms

> TODO

## Source code

## Gallery

> TODO

## Task repartition

In the source code, functions are defined in `.h` files in the `include` folder. The author of each functions is indicated with the `@author` flag. 

> TODO
