#include "RobotLeg.h"
#include "N20Servo.h"

RobotLeg::RobotLeg(float lengths [5])
{

  _MA = (N20Servo *) malloc(sizeof(N20Servo *));
  _MA = (N20Servo *) malloc(sizeof(N20Servo *));
  _a11=lengths[0];
  _a12=lengths[1];
  _a21=lengths[2];
  _a22=lengths[3];
  _d=lengths[4];

}

RobotLeg::~RobotLeg()
{
    //dtor
}

void RobotLeg::create_motors(){

  _MA = new N20Servo();
  _MB = new N20Servo();

}

void RobotLeg::setup_motors(int A_pins[3],float A_ks[3],int A_refs[2],int B_pins[3],float B_ks[3],int B_refs[2]){

  _MA->assignpins(A_pins);
  _MA->setk(A_ks);
  _MA->setrefs(A_refs);
  _MB->assignpins(B_pins);
  _MB->setk(B_ks);
  _MB->setrefs(B_refs);

}

void RobotLeg::goToF(float q1, float q2, int pwm){
    _q1=q1;
    _q2=q2;
    _MA->goTo(q1,pwm);
    _MB->goTo(q2,pwm);
}

void RobotLeg::goToI(float x, float y, int pwm){

float E1=-2*_a11*x;
float F1=-2*_a11*y;
float G1=_a11*_a11-_a12*_a12+x*x+y*y;

float E2=2*_a11*(-x+_d);
float F2=-2*_a11*y;
float G2=_d*_d+_a11*_a11-_a12*_a12+x*x+y*y-2*_d*x;

float q1=2*atan2(-F1+sqrt(E1*E1+F1*F1-G1*G1),G1-E1);
float q2=2*atan2(-F2-sqrt(E2*E2+F2*F2-G2*G2),G2-E2);

q2=q2*4068/71;
q1=q1*4068/71;

// Serial.print("q1: ");
// Serial.println(q1);
// Serial.print("q2: ");
// Serial.println(q2);
// Serial.print("x: " );
// Serial.println(x);
// Serial.print("y: ");
// Serial.println(y);

q1=constrain(q1,0,180);
q2=constrain(q2,0,180);

if(isnan(q1)){
  q1=_q1;
}
if(isnan(q1)){
  q1=_q2;
}

goToF(q1,q2,pwm);

}

int RobotLeg::getPos(int i){
    
    if(i==1){
        return _MA->readSens();
    }
    else{
        return _MB->readSens();
    }
}

void RobotLeg::forwardk(float q1,float q2){

q1=q1*71/4068;
q2=q2*71/4068;

float E =2*_a12*(_d+_a11*(cos(q2)-cos(q1)));
float F =2*_a11*_a12*(sin(q2)-sin(q1));
float G=_d*_d+2*_a11*_a11+2*_d*_a11*cos(q2)-2*_d*_a11*cos(q1)-2*_a11*_a11*cos(q2-q1);


float x= _d+_a11*cos(q2)+_a12*cos(2*atan2((-F+sqrt(E*E+F*F-G*G)),(G-E)));
float y= _a11*sin(q2)+_a12*sin(2*atan2((-F-sqrt(E*E+F*F-G*G)),(G-E)));

Serial.println(x);
Serial.println(y);

}
