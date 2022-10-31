#include "Pochitabot.h"

const int pinsM1[3] = {3,2,A0};
const int pinsM2[3] = {5,4,A2};
const int pinsM3[3] = {6,7,A4};
const int pinsM4[3] = {9,8,A6};
const int pinsM5[3] = {10,11,A8};
const int pinsM6[3] = {12,13,A10};
const int pinsM7[3] = {45,44,A12};
const int pinsM8[3] = {46,47,A14};
const float kA[3] = {2.0,1.0,0.001}; // PID values, kp, kd, ki
const int refsA[2] = {796,516}; //analog reference for angle 0 and 90 (from the horizontal)

RobotLeg * L11;
RobotLeg * L12;
RobotLeg * L21;
RobotLeg * L22;

Pochitabot * Pochi;

unsigned long timer = 0;
unsigned long dt = 200;

float xpos = 28.1;
float ypos = 45.0;
float a = 8.0;
float b = 3.0;
float r = 0;
float theta = 50;
float tt = 0;
bool c = false;
float dis = 19;

float leglengths[5] = {25.0,50.0,50.0,25.0,56.2};

void setup() {

L11 = new RobotLeg(leglengths);
L11 -> create_motors();
L11 -> setup_motors(pinsM2,kA,refsA,pinsM1,kA,refsA);
L12 = new RobotLeg(leglengths);
L12 -> create_motors();
L12 -> setup_motors(pinsM3,kA,refsA,pinsM4,kA,refsA);
L21 = new RobotLeg(leglengths);
L21 -> create_motors();
L21 -> setup_motors(pinsM6,kA,refsA,pinsM5,kA,refsA);
L22 = new RobotLeg(leglengths);
L22 -> create_motors();
L22 -> setup_motors(pinsM7,kA,refsA,pinsM8,kA,refsA);

Pochi = new Pochitabot();
Pochi -> registerlegs(L11,L12,L21,L22);

Serial.begin(9600);

timer=millis();

}

void loop() {

if(millis()-timer>=dt){
//r=a*b/(sqrt(a*sin(theta)*a*sin(theta)+b*cos(theta)*b*cos(theta)));
r=10;
theta=theta+3.141592/2.0;  
// c=!c;
// dis=19*c;
timer=millis();
}

// if(sin(theta)>0.0){
// c=0;
// }
// else{
//   c=1;
// }

// L11 -> goToI(xpos+r*cos(theta),57+c*r*sin(theta),210);
// L12 -> goToI(xpos+r*cos(theta),57+c*r*sin(theta),210);

// if(sin(theta+3.141592)>0.0){
// c=0;
// }
// else{
//   c=1;
// }

// L21 -> goToI(xpos+r*cos(theta+3.141592),57+c*r*sin(theta+3.141592),210);
// L22 -> goToI(xpos+r*cos(theta+3.141592),57+c*r*sin(theta+3.141592),210);

// L11 -> goToI(xpos,40+dis/2,200);
// L12 -> goToI(xpos,40+dis/2,200);
// L21 -> goToI(xpos,ypos-dis,200);
// L22 -> goToI(xpos,ypos-dis,200);

// L11 -> goToF(80-tt,110+tt,255);
// L12 -> goToF(80-tt,110+tt,255);
// L21 -> goToF(80-tt,110+tt,255);
// L22 -> goToF(80-tt,110+tt,255);

L11 -> goToI(28.1,45,210);
L12 -> goToI(28.1,45,210);

L21 -> goToI(xpos,55+r*sin(theta+3.141592),210);
L22 -> goToI(xpos,55+r*sin(theta+3.141592),210);

}
