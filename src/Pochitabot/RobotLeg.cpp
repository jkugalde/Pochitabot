#include "RobotLeg.h"
#include "N20Servo.h"

RobotLeg::RobotLeg(float lengths [5])
{

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

void RobotLeg::dirs(bool dir1, bool dir2)
{
  _M1.invdir(dir1);
  _M2.invdir(dir2);
}
void RobotLeg::motorpins(int pinsA [4], int pinsB [4]){
    _M1.assignpins(pinsA);
    _M2.assignpins(pinsB);
}

void RobotLeg::setks(float kA [3], float kB [3]){
    _M1.setk(kA);
    _M2.setk(kB);

}

void RobotLeg::goTo(float q1, float q2, int pwm){
    _q1=q1*71/4068;
    _q2=q2*71/4068;
    _M1.goTo(q1,pwm);
    _M2.goTo(q2,pwm);


}

void RobotLeg::ik(float x, float y, int pwm){


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

}

int RobotLeg::getPos(int i){
    
    if(i==1){
        return _M1.readSens();
    }
    else{
        return _M2.readSens();
    }
}

void RobotLeg::turnoff(int i){

    if(i==1){
    _M1.turnoff();
    }
    else if(i==2){
     _M2.turnoff();
    }
    else{
    _M1.turnoff();
    _M2.turnoff();
    }


}

void RobotLeg::setrefs(int refA[2],int refB[2]){
    _M1.setrefs(refA);
    _M2.setrefs(refB);
}

void RobotLeg::fk(){

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
