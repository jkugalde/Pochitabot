#ifndef N20Servo_h
#define N20Servo_h

#include "Arduino.h"


class N20Servo
{

    public:

    N20Servo();
    ~N20Servo();
    void setk(float k [3]);
    int readSens(); //reads the sensor
    void assignpins(int pins [4]); //setup pins
    void act(); //actuates
    void goTo(int target, int maxvel); //go to angle with maxvel in pwm
    void setrefs(int refs [2]); //refs for 90 and 0 degrees
    void turnoff(); //sleep
    float setKgrad();
    void invdir(bool dinv);

    private:

      int _sensval;
      int _pindir;
      int _dir;
      int _pinpwm;
      int _pinsens;
      int _pinslp;
      float _Kp;
      float _Kd;
      float _Ki;
      int _preverror;
      int _Ierror;
      int _ref_0;
      int _ref_90;
      float _kgrad;
      int _power;
      float _thI;
      bool _inv;

};

#endif //N20Servo_H
