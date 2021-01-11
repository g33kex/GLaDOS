
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

### Move precisely 

#### Basic Control

The robot moves using a differential drive with direct control over the motor's duty cycle. Turning the left motor with a higher duty cycle than the right motor will make the robot curve to the right, and turning the right motor with a higher duty cycle than the left motor will make the robot curve to the left.  
Turning the left motor in reverse from the right motor is used to make the robot turn in place.

Here is the algorithm to face a target :  
```C
start_motors();

do {
    update_rotation();
    angle = angle_between_robot_and_target();

    if(angle>0) {
        set_motors_duty(-DUTY, DUTY);
    } else if(angle<0) {
        set_motors_duty(DUTY, -DUTY);
    }
} while(abs(angle)>ANGULAR_PRECISION);

stop_motors();
```

And the algorithm to go to a target :
```C
void move_to(Vector target) {
    set_motors_duty(DUTY, DUTY);
    start_motors();

    while(distance(target, robot_pos)>=PRECISION) {
        update_rotation();
        update_position();

        angle = angle_between_robot_and_target();

        if(angle < 0) { // Turn Right
            set_motors_duty(DUTY, DUTY-SMALL_CONSTANT);
        }
        else if(angle > 0) { // Turn Left
            set_motors_duty(DUTY-SMALL_CONSTANT, DUTY);
        }
        else { // Go Straight
            set_motors_duty(DUTY, DUTY);
        }
    }

    stop_motors();
}
```

#### Position computation

To update the position of the robot, we first read the position of the encoder of the motors and convert that to a linear distance. Then we take the mean distance of the two wheels to compute the distance travelled by the robot.

Here is the corresponding C pseudo-code :
```C
//Get encoder positions
l = get_left_wheel_encoder_position();
r = get_right_wheel_encoder_position();

//Calculate linear travelled distance of each wheels
SR = ((r-right_wheel_previous_pos)*WHEEL_CIRCUMFERENCE)/360.0;
LR = ((l-left_wheel_previous_pos)*WHEEL_CIRCUMFERENCE)/360.0;

//Update last positions
right_wheel_previous_pos = r;
left_wheel_previous_pos = l;

//Compute mean distance
distance = (SR+LR)/2;

//Add travelled distance to robot position
Vector motion = {meanDistance*cos(radians(robot_pos.rotation)), meanDistance*sin(radians(robot_pos.rotation))};
robot_pos.p = vector_add(robot_pos.p,motion);
```

#### Rotation computation

To compute the rotation, we use fuse the data from the gyroscope and the compass. Here GYRO_TRUST_RATIO = 0.95, which means we only trust the position given from the compass at 5%. This allows to compensate the gyro drift.

```C
k = GYRO_TRUST_RATIO;
//Get the amount of rotation given by the gyro since last call
gyro_rot = get_gyro_delta(); 
//Get rotation given by the compass
compass_rot = get_orientation();
//Add gyro rotation to robot rotation
robot_pos.rotation += gyro_rot;
//Fuse in the compass data
robot_pos.rotation = (robot_pos.rotation*k) + (compass_rot*(1.0-k));
//Make sure the angle is between 0 and 360
robot_pos.rotation = robot_pos.rotation%360;
```

### Pickup ball

> TODO (Florian)

### Place ball 

> TODO (Mathieu)

#### In the cube

#### In the pyramid

### Find random cube

> TODO (Mathieu)

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

- Florian : robot physical assembly and testing
    * Took care of the physical assembly of the robot
    * Worked on the grab and place functions
    * Carried out the testing of the robot
- Mathieu : high level functions and sensors
    * Set up the sensors and the interfaces to them
    * Made the procedure to find the random cube
    * Worked on the procedure to pickup the ball from the code
    * Worked on the procedure to place the ball in the code/pyramid
- Virgile : motion system and integration
    * Did the Makefile, code structure, and integration
    * Took care of the motion system
    * Made a Vector library to support the motion system
    * Made the function that uses Tacheometry to update the robot's position
    * Made the function that uses sensor fusion of the compass and gyro to update the robot's rotation
    * Made a motion procedures to move the robot to a precise position and rotation

