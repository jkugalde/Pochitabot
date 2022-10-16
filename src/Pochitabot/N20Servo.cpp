#include "N20Servo.h"

N20Servo::N20Servo()
{

_Kp=0; //pid constants and variables initialization
_Kd=0;
_Ki=0;
_preverror=0;
_power=0;
_thI=0;
_inv=false;

}

void N20Servo::assignpins(int pins [4]){

  _pindir=pins[0];
  _pinpwm=pins[1];
  _pinsens=pins[2];
  _pinslp=pins[3];
  pinMode(_pindir,OUTPUT);
  pinMode(_pinpwm,OUTPUT);
  digitalWrite(_pinpwm,LOW);
  pinMode(_pinsens,INPUT);
  pinMode(_pinslp,OUTPUT);

}

N20Servo::~N20Servo()
{
    //dtor
}

void N20Servo::invdir(bool dinv){

_inv=dinv;

}

int N20Servo::readSens(){ //read the analog value of the sensor

	_sensval=analogRead(_pinsens);
	return _sensval;

}

void N20Servo::turnoff(){

digitalWrite(_pinslp,LOW);

}

void N20Servo::act(){

  digitalWrite(_pinslp,HIGH);
	digitalWrite(_pindir,_dir);
  analogWrite(_pinpwm,_power);

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
    _dir=1+-1*_inv;
    _power=pow;
  }
  else{  
    _dir=0+_inv;
    _power=-pow;
  }

  act();

}


