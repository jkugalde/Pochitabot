#include "N20Servo.h"

N20Servo::N20Servo()
{

_Kp=0; //pid constants and variables initialization
_Kd=0;
_Ki=0;
_preverror=0;
_thI=10;

}

void N20Servo::setupmotor(int pins[3],float k[3],int refs[2]){

}

void N20Servo::assignpins(int pins [3]){

  _pinA=pins[0];
  _pinB=pins[1];
  _pinsens=pins[2];
  pinMode(_pinA,OUTPUT);
  pinMode(_pinB,OUTPUT);
  digitalWrite(_pinA,LOW);
  digitalWrite(_pinB,LOW);
  pinMode(_pinsens,INPUT);

}

N20Servo::~N20Servo()
{
    //dtor
}


int N20Servo::readSens(){ //read the analog value of the sensor

	_sensval=analogRead(_pinsens);
	return _sensval;

}

void N20Servo::act(int pA, int pB){

	analogWrite(_pinA,pA);
  analogWrite(_pinB,pB);

}

void N20Servo::setk(float k [3]){ //assign pid constants

	_Kp=k[0];
  _Kd=k[1];
  _Ki=k[2];
  
}

float N20Servo::setKgrad(){ //transformation constant from degrees to values.

  _kgrad=float((_ref_90-_ref_0)/90.0);
  return _kgrad;

}

void N20Servo::setrefs(int refs[2]){ 
  _ref_0=refs[0];
  _ref_90=refs[1];
  setKgrad();
}

void N20Servo::goTo(int target, int maxvel){

  target=int(_kgrad*target)+_ref_0;
  //Serial.print("Position: ");
  int pos = readSens();
  //Serial.print(pos);
  int error = target-pos;
  //Serial.print("  ");
  //Serial.println("error: ");
  int Derror = error-_preverror;
  int Ierror=Ierror+error; 

  if(abs(error)>_thI){
    Ierror=0;
  }
  
  int pow=int(_Kp*error)-int(_Kd*Derror)+int(_Ki*Ierror);

  _preverror=error;
  
  pow=constrain(pow,-maxvel,maxvel);
  
  if(pow>0){ //direction
    act(pow,0);
  }
  else{  
    act(0,-pow);
  }

}


