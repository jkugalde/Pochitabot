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
    int getPos(int i);
    void forwardk();
    void create_motors();
    void setup_motors(int A_pins[3],float A_ks[3],int A_refs[2],int B_pins[3],float B_ks[3],int B_refs[2]);

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
