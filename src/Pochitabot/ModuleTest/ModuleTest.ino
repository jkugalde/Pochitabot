#include "N20Servo.h"

const int pinsA1[3] = {46,47,A14};

const float kA[3] = {4.0,10,0.001}; // PID values, kp, kd, ki
const int refsA[2] = {796,516}; //analog reference for angle 0 and 90 (from the horizontal)
int var = 90;

unsigned long timer = 0;
unsigned long dt = 5;
float theta = 0;
float c= 0;

N20Servo MA1;

void setup() {

 MA1.assignpins(pinsA1);
 MA1.setk(kA); 
 MA1.setrefs(refsA);
 Serial.begin(9600);
 timer=millis();

}

void loop() {

if(millis()-timer>=dt){
c=45*sin(theta);
timer=millis();
theta=theta+0.02;  
}
MA1.goTo(90,130);

}

