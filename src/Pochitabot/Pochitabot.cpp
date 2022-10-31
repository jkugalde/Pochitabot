#include "Pochitabot.h"

Pochitabot::Pochitabot(){

}

Pochitabot::~Pochitabot()
{
    //dtor
}

void Pochitabot::registerlegs(RobotLeg * L1, RobotLeg * L2, RobotLeg * L3, RobotLeg * L4){

L11 = L1;
L12 = L2;
L21 = L3;
L22 = L4;

}

void Pochitabot::movexy(float x, float y, int pwm){

float x2 = 27;
float diff = x2-x;
x2=x2+diff;

L11 -> goToI(x,y,pwm);
L12 -> goToI(x,y,pwm);
L21 -> goToI(x2,y,pwm);
L22 -> goToI(x2,y,pwm);

}

void Pochitabot::moveang(float q1, float q2, int pwm){

L11 -> goToF(q1,q2,pwm);
L12 -> goToF(q1,q2,pwm);
L21 -> goToF(q1,q2,pwm);
L22 -> goToF(q1,q2,pwm);

}
