#include "N20Servo.h"

const int pinsA1[3] = {5,4,A2};

const float kA[3] = {2,0.2,0}; // PID values, kp, kd, ki
const int refsA[2] = {796,516}; //analog reference for angle 0 and 90 (from the horizontal)
int var = 0;

N20Servo MA1;

void setup() {

 MA1.assignpins(pinsA1);
 MA1.setk(kA); 
 MA1.setrefs(refsA);
 Serial.begin(9600);

}

void loop() {

MA1.goTo(var,180);
Serial.println(MA1.readSens());

}

