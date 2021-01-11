
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

The C sourcecode is avaliable on [GitHub](https://github.com/g33kex/GLaDOS). Headers are in the `include` folder and sources in the `src` folder.

To download the source code, please use :
```bash
git clone https://github.com/g33kex/GLaDOS.git
git submodule update --init --recursive
```

### Compilation Instructions

The software can be compiled directly from the robot, or cross-compiled from another computer. When cross-compiling, make sure you have [Docker](https://www.docker.com/) installed and running. 

Whether you're compiling from the robot or cross-compiling, the procedure is the same : 
```
make
```

The executable will be located in `bin/GLaDOS`. You can copy it to the robot manually, or automatically using `make install` if you have properly configured an ssh connection to the robot named `robot`. 

### Usage Instructions

Many tests and manual operations can be performed, please see `./GLaDOS help` for help. For instance, to run the full simulation, one must use `./GLaDOS main`. In case of an error, to immediatly stop the motors you can use `./GLaDOS stop`. 

## Gallery

> TODO

## Task repartition

In the source code, functions are defined in the headers (`.h`) files in the `include` folder. The author of each functions is indicated with the `@author` flag. 

- Florian
    * Took care of the physical assembly of the robot
    * Worked on the grab and place functions
    * Carried out the testing of the robot
- Mathieu
    * Set up the sensors and the interfaces to them
    * Made the procedure to find the random cube
    * Worked on the procedure to pickup the ball from the code
    * Worked on the procedure to place the ball in the code/pyramid
- Virgile
    * Did the Makefile, code structure, and integration
    * Took care of the motion system
    * Made a Vector library to support the motion system
    * Made the function that uses Tacheometry to update the robot's position
    * Made the function that uses sensor fusion of the compass and gyro to update the robot's rotation
    * Made a motion procedures to move the robot to a precise position and rotation



> TODO
