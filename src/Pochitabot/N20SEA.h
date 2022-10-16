#ifndef N20SEA_h
#define N20SEA_h

#include "N20Servo.h"

class N20SEA : public N20Servo {

  public:

  N20SEA();
  ~N20SEA();
  void assigntorquesens(int i);
  float torque();
  void setrefsB(int refs[2]);
  float setKgradB();

  private:

    int _senspin;
    int _ref_0B;
    int _ref_90B;
    float _kgradB;
 
};

#endif 
