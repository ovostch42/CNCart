#include "Arduino.h"
#include "MOSIKStep.h"
#include "StepHardware.h"

/*
byte _actM1, _actM2, _dirM1, _dirM2, _archtrig, _archecho;
int _mindelay, _maxdelay;
int step_now = 0;
int _Dbase;																
int acdec_step = 400;
float pi = 3.14, _diam;
*/

//инициализация тележки
//actM1 - step пин 1-ого мотора; actM2 - step пин 2-ого мотора;
//dirM1 - dir пин 1-ого мотора; dirM2 - dir пин 2-ого мотора;
//Dbase - ширина колёсной базы
//mindelay - минимальная задержка между шагами мотора
//maxdelay - максимальная задержка между шагами мотора
//diam - диаметр колеса
int _mindelay, _maxdelay;
int _Dbase;																
int acdec_step = 400;
int step_now = 0;
float pi = 3.14, _diam;
byte _dirM1, _dirM2, _actM1, _actM2;


MOSIKStep::MOSIKStep(byte actM1, byte actM2, byte dirM1, byte dirM2, int Dbase, int mindelay, int maxdelay, float diam){
  _actM1 = actM1;
  _actM2 = actM2;
  _dirM1 = dirM1;
  _dirM2 = dirM2;
  _diam = diam;
  _Dbase = Dbase;
  _mindelay = mindelay;
  _maxdelay = maxdelay;
}


float MOSIKStep::step_acdec(float step){
  int del_out = ((_maxdelay-_mindelay)*(step-step_now) + step*_mindelay)/(step);
  
  return del_out;
}

//проезд по шагам
void MOSIKStep::przd_base(int step, bool isTurn, byte dir){  
  int del_arr_acdec[step/2];
  step_now = 0;

  StepHardware mot1(_actM1,_dirM1);
  StepHardware mot2(_actM2,_dirM2);

  if (isTurn){
    mot2.setDir(dir);
    mot1.setDir(!dir);
  }else{
    mot2.setDir(dir);
    mot1.setDir(dir);
}

  for (int iiii = 0; iiii < step/2; iiii++){
    del_arr_acdec[iiii] = step_acdec(step/2);
 
    step_now += 1;
  }

  step_now = 0;
  for (int i = 0; i < step/2; i+=2){
    mot2.step(1000);
    mot1.step(1000);
    
  }

  step_now = 0;
  for (int i = 0; i < step/4; i++){
    mot2.step(1000);
    mot1.step(1000);
    
  }
  step_now = 0;
  for (int i = step/2; i > 0; i--){
    mot2.step(1000);
    mot1.step(1000);
  
  }
  
} 

//проезд по сантиметрам
void MOSIKStep::przd_cm(float cm, byte dir){
  przd_base(200*cm/(pi*_diam),0,dir);
}

//поворот
void MOSIKStep::turn(float deg, byte dir){
  przd_base(deg*_Dbase/(1.8*_diam),1,dir);
}