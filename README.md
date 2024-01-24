# Line Follower
## Introduction

A line follower is a type of autonomous robot or vehicle (in our case a robot that sort of looks like a vehicle) designed to follow a visible path or line on the ground. This path is typically marked with a contrasting color, such as black on a white surface (like in our case) or vice versa. The robot uses sensors, usually infrared sensors, to detect the line and make adjustments to stay on course. The basic working principle involves the use of sensors to detect the contrast between the line and its surroundings. The sensors generate electrical signals based on the intensity of light reflected from the surface. By analyzing these signals, the robot can determine whether it is on the line, off to one side, or completely off the track. To navigate along the line, the robot employs control algorithms that enable it to make adjustments to its speed and direction in real-time. For example, if the robot drifts to the right of the line, it may increase the speed of the left motor or decrease the speed of the right motor to steer itself back onto the correct path. In our case, the robot uses PID control to stay on track.

## What is PID?

PID (or Proportional-Integral-Derivative) is a feedback control system widely used in engineering and automation. PID controllers are commonly used in various applications to regulate and control processes, such as temperature, speed, position etc.

How it works: <br/>

1. **Proportional**: The proportional term is directly proportional to the current error, which is the difference between the desired setpoint and the actual value. It produces an output that is proportional to the present error. This term contributes to the overall correction based on the magnitude of the error. <br/>

2. **Integral**: The integral term considers the accumulated sum of past errors over time. It is responsible for eliminating any residual steady-state error that might persist with only proportional control. The integral term helps to reduce the long-term error by adjusting the output based on the accumulated historical error. <br/>

3. **Derivative**: The derivative term is proportional to the rate of change of the error. It anticipates future behavior of the system by considering how quickly the error is changing. The derivative term helps to dampen the system's response, preventing overshooting and oscillations. <br/>

A PID controller's output is the sum of these three terms, each adjusted by respective constants (proportional gain denoted by **kp**, integral gain denoted by **ki**, and derivative gain denoted by **kd**). The combination of these terms allows the controller to provide a more accurate and responsive control action, improving the system's stability and performance.
