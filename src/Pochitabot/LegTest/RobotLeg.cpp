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

float A = x;
float B = y;
float C = (_a11*_a11-_a12*_a12+x*x+y*y)/(2*_a11);

float q1 = 2*atan2(-B-sqrt(A*A+B*B-C*C),-A-C);

A = x - _d;
B = y;
C = (_a22*_a22+_d*_d-_a21*_a21-2*x*_d+x*x+y*y)/(2*_a22);

float q2 = 2*atan2(-B+sqrt(A*A+B*B-C*C),-A-C);

q2=q2*4068/71+360;
q1=360+q1*4068/71;

Serial.print("q1: ");
Serial.println(q1);
Serial.print("q2: ");
Serial.println(q2);

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

void RobotLeg::forwardk(){

float A=2*_a22*_a21*sin(_q2)-2*_a11*_a21*cos(_q1);
float B = 2*_a22*_d-2*_a11*_a22*cos(_q1)+2*_a22*_a21*cos(_q2);
float C1 = _a11*_a11-_a12*_a12+_a21*_a21+_a22*_a22+_d*_d;
float C2 = -_a11*_a21*sin(_q1)*sin(_q2)-2*_a11*_d*cos(_q1)+2*_a21*_d*cos(_q2)-2*_a11*_a21*cos(_q1)*cos(_q2);
float C = C1+C2;
float theta2=2*atan2((A+sqrt(A*A+B*B-C*C)),(B-C));
float theta1=asin((_a22*sin(theta2)+_a21*sin(_q2)-_a11*sin(_q1))/_a12);
_x=_a11*cos(_q1)+_a12*cos(theta1);
_y=_a11*sin(_q1)+_a12*sin(theta1);
Serial.println(_x);
Serial.println(_y);

}
