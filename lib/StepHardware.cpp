#include "Arduino.h"
#include "StepHardware.h"

StepHardware::StepHardware(byte actM, byte dirM){
  _actM = actM;
  _dirM = dirM;

  pinMode(_actM,OUTPUT);
  pinMode(_dirM,OUTPUT);
}

void StepHardware::step(int delay){
    digitalWrite(_actM,HIGH);
    delayMicroseconds(delay);
    digitalWrite(_actM,LOW);
    delayMicroseconds(delay);
}

void StepHardware::setDir(bool dir){
  Serial.println(_dirM);
  digitalWrite(_dirM,dir);
}

//void step