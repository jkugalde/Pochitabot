#include "RobotLeg.h"

const int pinsA1[3] = {10,11,A8};
const int pinsA2[3] = {12,13,A10};
const float kA[3] = {3.0,4.0,0.0001}; // PID values, kp, kd, ki
const int refsA[2] = {796,516}; //analog reference for angle 0 and 90 (from the horizontal)

RobotLeg * L11;

float leglengths[5] = {25.0,50.0,50.0,25.0,56.2};

unsigned long timer = 0;
unsigned long dt = 10;

float xpos = 28.1;
float ypos = 54;
float x = 0;
float y = 0;

//elliptical

float a = 11.0;
float b = 4.0;
int c = 1;

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
r=a*b/(sqrt(a*sin(theta)*a*sin(theta)+b*cos(theta)*b*cos(theta)));
timer=millis();
theta=theta+0.05;  
}

L11 -> goToI(27+r*cos(theta),54+r*sin(theta),130);

}
