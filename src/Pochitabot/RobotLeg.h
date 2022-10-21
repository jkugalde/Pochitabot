#ifndef RobotLeg_h
#define RobotLeg_h

#include "N20Servo.h"

class RobotLeg
{

    public:
    N20Servo * _MA;
    N20Servo * _MB;
    RobotLeg(float lengths[5]);
    ~RobotLeg();
    void goToF(float q1, float q2, int pwm);
    void goToI(float x, float y, int pwm);
    void registermotors(N20Servo * MA, N20Servo * MB);
    int getPos(int i);
    void forwardk();

    private:

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
