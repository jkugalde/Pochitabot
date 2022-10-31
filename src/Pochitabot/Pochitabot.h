#ifndef Pochitabot_h
#define Pochitabot_h

#include "RobotLeg.h"

class Pochitabot{

  public:

  RobotLeg * L11;
  RobotLeg * L12;
  RobotLeg * L21;
  RobotLeg * L22;
  Pochitabot();
  ~Pochitabot();
  void registerlegs(RobotLeg * L1, RobotLeg * L2, RobotLeg * L3, RobotLeg * L4);
  void movexy(float x,float y, int pwm);
  void moveang(float q1, float q2, int pwm);
 
};

#endif 
