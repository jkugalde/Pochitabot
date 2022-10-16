#ifndef RobotLeg_h
#define RobotLeg_h

#include "N20Servo.h"

class RobotLeg
{

    public:
    RobotLeg(float lengths[5]);
    ~RobotLeg();
    void motorpins(int pinsA [4], int pinsB [4]);
    void goTo(float q1, float q2, int pwm);
    void setrefs(int refA[2], int refB[2]);
    void setks(float kA [3], float kB [3]);
    void turnoff(int i);
    void fk();
    void ik(float x, float y, int pwm);
    void dirs(bool d1, bool d2);
    int getPos(int i);
    private:
      N20Servo _M1;
      N20Servo _M2;
      float _x;
      float _y;
      float _q1;
      float _q2;
      float _a11;
      float _a12;
      float _a21;
      float _a22;
      float _d;


};

#endif //RobotLeg
