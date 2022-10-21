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

void RobotLeg::registermotors(N20Servo * MA, N20Servo * MB){

  _MA=MA;
  _MB=MB;

}

void RobotLeg::goToF(float q1, float q2, int pwm){
    _q1=q1*71/4068;
    _q2=q2*71/4068;
    _MA->goTo(q1,pwm);
    _MB->goTo(q2,pwm);
}

void RobotLeg::goToI(float x, float y, int pwm){


float C = sqrt(x*x+y*y);
float nu = atan2(y,x);
float gamma = acos((-_a12*_a12+_a11*_a11+C*C)/(2*_a11*C));
float q1 = nu+gamma;
float e = sqrt((_d-x)*(_d-x)+y*y);
float fi = atan2(y,_d-x);
float epsilon = acos((-_a22*_a22+_a21*_a21+e*e)/(2*_a21*e));
float q2=3.14-epsilon-fi;

Serial.println(q1*4068/71);
Serial.println(q2*4068/71);

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
