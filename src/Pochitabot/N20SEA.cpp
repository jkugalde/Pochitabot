#include "N20SEA.h"

N20SEA::N20SEA(){

}

N20SEA::~N20SEA()
{
    //dtor
}

float N20SEA::torque(){

return readSens()-analogRead(_senspin)+20;

}

float N20SEA::setKgradB(){ //transformation constant from degrees to values.

  _kgradB=float((_ref_90B-_ref_0B)/90.0);
  return _kgradB;

}

void N20SEA::assigntorquesens(int i){

  _senspin = i;
  pinMode(_senspin,INPUT);

}

void N20SEA::setrefsB(int refs[2]){

_ref_0B=refs[0];
_ref_90B=refs[1];

}