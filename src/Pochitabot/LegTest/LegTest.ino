#include "RobotLeg.h"

const int pinsA1[3] = {2,3,A0};
const int pinsA2[3] = {5,4,A2};
const float kA[3] = {1.0,0.1,0}; // PID values, kp, kd, ki
const int refsA[2] = {796,516}; //analog reference for angle 0 and 90 (from the horizontal)

N20Servo * MA1;
N20Servo * MA2;

RobotLeg * L11;

float leglengths[5] = {25.0,50.0,50.0,25.0,54};

unsigned long timer = 0;
unsigned long dt = 2;

float xpos = 27.0;
float ypos = 50.0;

//elliptical

float a = 15;
float b = 5;

float r = 0;
double theta = 0;

void setup() {

L11 = new RobotLeg(leglengths);
L11 -> create_motors();
L11 -> setup_motors(pinsA2,kA,refsA,pinsA1,kA,refsA);
Serial.begin(9600);

}

void loop() {

if(millis()-timer>=dt){
float b2 = b*cos(theta);
float a2 = a*sin(theta);
r = a*b/(sqrt(b*b+a*a));
theta = theta+0.08;
timer=millis();
}

L11->goToI(xpos+r*cos(theta),ypos+r*sin(theta),180);

}
