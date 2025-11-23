#include "Arduino.h"
#include "MOSIKStep.h"

byte _actM1, _actM2, _dirM1, _dirM2;
int _mindelay, _maxdelay;
int step_now = 0;
int _Dbase;																
int acdec_step = 400;
float pi = 3.14, _diam;

MOSIKStep::MOSIKStep(byte actM1, byte actM2, byte dirM1, byte dirM2, int Dbase, int mindelay, int maxdelay, float diam){
  _diam = diam;
  _Dbase = Dbase;
  _mindelay = mindelay;
  _maxdelay = maxdelay;
  _actM1 = actM1;
  _actM2 = actM2;
  _dirM1 = dirM1;
  _dirM2 = dirM2;

  pinMode(_actM1,OUTPUT);
  pinMode(_actM2,OUTPUT);
  pinMode(_dirM1,OUTPUT);
  pinMode(_dirM2,OUTPUT);
}

float MOSIKStep::step_acdec(float step){
  int del_out = ((_maxdelay-_mindelay)*(step-step_now) + step*_mindelay)/(step);
  
  return del_out;
}

void MOSIKStep::przd_base(int step, bool isTurn, byte dir){  
  int del_arr_acdec[step/2];
  step_now = 0;
  digitalWrite(13,1);
  digitalWrite(12,1);
  digitalWrite(11,1);
  digitalWrite(10,1);

  if (isTurn){
    digitalWrite(_dirM1,dir);
    digitalWrite(_dirM2,!dir);
  }else{
    digitalWrite(_dirM1,dir);
    digitalWrite(_dirM2,dir);
}

  for (int iiii = 0; iiii < step/2; iiii++){
    del_arr_acdec[iiii] = step_acdec(step/2);
 
    step_now += 1;
  }

  step_now = 0;
  for (int i = 0; i < step/2; i+=2){
    digitalWrite(_actM1,HIGH);
    digitalWrite(_actM2,HIGH);
    delayMicroseconds(del_arr_acdec[i]);
    digitalWrite(_actM1,LOW);
    digitalWrite(_actM2,LOW);
    delayMicroseconds(del_arr_acdec[i]);
    step_now += 1;
  }

  step_now = 0;
  Serial.println(step);
  for (int i = 0; i < step/4; i++){
    digitalWrite(_actM1,HIGH);
    digitalWrite(_actM2,HIGH);
    delayMicroseconds(_mindelay);
    digitalWrite(_actM1,LOW);
    digitalWrite(_actM2,LOW);
    delayMicroseconds(_mindelay);
    step_now += 1;
  }
  step_now = 0;
  for (int i = step/2; i > 0; i--){
    digitalWrite(_actM1,HIGH);
    digitalWrite(_actM2,HIGH);
    delayMicroseconds(del_arr_acdec[i]);
    digitalWrite(_actM1,LOW);
    digitalWrite(_actM2,LOW);
    delayMicroseconds(del_arr_acdec[i]);
    step_now += 1;
  }
} 

void MOSIKStep::przd_cm(float cm, byte dir){
  Serial.println(200*cm/(pi*_diam));
  przd_base(200*cm/(pi*_diam),0,dir);
}

void MOSIKStep::turn(float deg, byte dir){
  przd_base(deg*_Dbase/(1.8*_diam),1,dir);
}
