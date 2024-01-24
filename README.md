# Line Follower
## Introduction

A line follower is a type of autonomous robot or vehicle (in our case a robot that sort of looks like a vehicle) designed to follow a visible path or line on the ground. This path is typically marked with a contrasting color, such as black on a white surface (like in our case) or vice versa. The robot uses sensors, usually infrared sensors, to detect the line and make adjustments to stay on course. The basic working principle involves the use of sensors to detect the contrast between the line and its surroundings. The sensors generate electrical signals based on the intensity of light reflected from the surface. By analyzing these signals, the robot can determine whether it is on the line, off to one side, or completely off the track. To navigate along the line, the robot employs control algorithms that enable it to make adjustments to its speed and direction in real-time. For example, if the robot drifts to the right of the line, it may increase the speed of the left motor or decrease the speed of the right motor to steer itself back onto the correct path. In our case, the robot uses PID control to stay on track.

## What did we have to do?

As teams of three, we had a day to spend on college grounds to put together a line follower that would successfully complete a given circuit within a timeframe. Ideally, for maximum grade, our little Lightning McQueen was supposed to complete the circuit in under 20 seconds. During grading, we were allowed to showcase the line follower 3 times before our grade was calculated using the best time from those 3 tries. Our luck made it so we missed the maximum grade by one second, but nonetheless it was a great performance since 3 hours before we presented the project nothing worked and we were about to blow up our battery two times.

## What is PID?

PID (or Proportional-Integral-Derivative) is a feedback control system widely used in engineering and automation. PID controllers are commonly used in various applications to regulate and control processes, such as temperature, speed, position etc.

How it works: <br/>

1. **Proportional**: The proportional term is directly proportional to the current error, which is the difference between the desired setpoint and the actual value. It produces an output that is proportional to the present error. This term contributes to the overall correction based on the magnitude of the error. <br/>

2. **Integral**: The integral term considers the accumulated sum of past errors over time. It is responsible for eliminating any residual steady-state error that might persist with only proportional control. The integral term helps to reduce the long-term error by adjusting the output based on the accumulated historical error. <br/>

3. **Derivative**: The derivative term is proportional to the rate of change of the error. It anticipates future behavior of the system by considering how quickly the error is changing. The derivative term helps to dampen the system's response, preventing overshooting and oscillations. <br/>

A PID controller's output is the sum of these three terms, each adjusted by respective constants (proportional gain denoted by **kp**, integral gain denoted by **ki**, and derivative gain denoted by **kd**). The combination of these terms allows the controller to provide a more accurate and responsive control action, improving the system's stability and performance.

## How did we use PID for our line follower?

In truth, our team assigned values to kp, ki and kd by trial and error, until we finally hit the right set of values that would stabiilize our line follower. In reality, this is how a PID controller should work for a line follower: <br/>

1. **Error Calculation**: Calculate the error, which is the difference between the desired position (center of the line) and the actual position of the robot based on sensor readings. <br/>
2. **P control**: Adjust the robot's steering based on the proportional term. If the robot is to the right of the line, increase the left motor speed or decrease the right motor speed (and vice versa). The amount of adjustment is proportional to the error. <br/>
3. **I control**: Address any persistent steady-state error by using the integral term. Sum up the errors over time and apply a correction to the motor speeds. <br/>
4. **D control**: Add damping to the system by considering the rate of change of the error. <br/>
5. **Combine PID Terms**: Calculate the PID output by summing the proportional, integral, and derivative terms with their respective coefficients : PID Output = (p * kp) + (i * ki) + (k * kd). <br/>
6. **Apply PID and tune parameters**: Apply the PID output to adjust the speeds of the robot's motors which will results in corrections that bring the robot back to the line and fine-tune the gains experimentally to achieve the desired line-following performance.