## Summary

Pochitabot is a tetrapod that uses my N20 series elastic actuator. The modules are paired in each leg in a 5 bar mechanism configuration. Currently, it has position control and potential torsion sense (not yet implemented in the software). 

Parts are [HERE](https://grabcad.com/library/tetrapod-robot-1).

<img src="/imgs/pochi.png" width="350">

In the maths folder there is a file that plots the task space of the leg, an ellipse and the joint angles to perform such ellipse, as the first approximation to a walking curve.

<img src="/imgs/tspace.png" width="350">

<img src="/imgs/joinpos.png" width="350">

There are 3 programs in the src folder. One is ModuleTest, which is a sweep, LegTest, which draws an ellipse, and Pochitabot, where every leg draws an ellipse.

The proper documentation of the code is not done yet.

## Further work

### General

- Change the microcontroller to a Teensy, the Arduino Mega does not have enough pwm pins. I'm also not sure if the microcontroller is fast enough.
- Implement trajectory generation and speed/acceleration control.

### Mechanical

- To strengthen and characterize the servo module design.
- To strengthen and characterize the leg module design.
- Optimize leg length. 
- To analyze the inclusion of a toe.

### Electrical

- To make a PCB.
- Add a button and a switch.

### Software

- Implement torsion sensing.
- To find a way to deal with the singularities and solve the inverse kinematics for the other quadrants.
