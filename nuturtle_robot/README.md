# nuturtle_robot
* A package that provides an interface for hardware on the Turtlebot. Converts body twists to wheel commands and calculates joint states using encoders.
* Author: Arun Kumar

## Nodes
* turtle_interface
    - converts body twists to wheel commands
    - calculates joint states using encoders
* follow_circle
    - makes the robot follow a circle of a specific radius at a specific speed

## Launch Files
* basic_remote.launch
    - launches serial_node on turtlebot to communicate with hardware
* odom_teleop.launch
    - allows teleoperation of turtlebot
    - loads turtlebot in rviz
    - tracks odometry
    - contains arguement to launch follow_circle instead of teleoperation node
```
roslaunch nuturtle_robot odom_teleop.launch
```

## Experiment 1
* Drive robot forward and barckward in straight line (pure translation)
* Stop at initial configuration
* Record odometry:
    * x = 0.0302
    * y = 0.0165
    * θ = 0.000600 rad <br/>
![Experiment1](gifs/experiment1.gif)
![Screencast1](gifs/screen1.gif) <br/>
Note: Gif only shows portion of experiment

## Experiment 2
* Rotate robot in place clockwise and counter clockwise (pure rotation)
* Stop at initial configuration
* Record odometry:
    * x = 0.0000445
    * y = -0.0000181
    * θ = 0.180 rad <br/>
![Experiment2](gifs/experiment2.gif)
![Screencast2](gifs/screen2.gif) <br/>
Note: Gif only shows portion of experiment

## Experiment 3
* Drive robot in circle clockwise and counter clockwise (translation plus rotation)
* Stop at initial configuration
* Record odometry:
    * x = -0.0290
    * y = 0.0633
    * θ = 0.398 rad <br/>
![Experiment3](gifs/experiment3.gif)
![Screencast3](gifs/screen3.gif) <br/>
Note: Gif only shows portion of experiment

## Experiment 4
* Drive robot in circle clockwise and counter clockwise (translation plus rotation)
* Goal: produce significantly worse results that experiment 3
    * Increased robot speed
    * Increased circle radius
* Stop at initial configuration
* Record odometry:
    * x = -0.282
    * y = 0.205
    * θ = 1.74 rad <br/>
![Experiment4](gifs/experiment4.gif)
![Screencast4](gifs/screen4.gif) <br/>
Note: Gif only shows portion of experiment