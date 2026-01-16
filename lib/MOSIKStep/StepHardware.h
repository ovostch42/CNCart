#ifndef _StepHardware_h_
#define _StepHardware_h_

#include <Arduino.h>

class StepHardware {

  public:

    StepHardware(byte actM, byte dirM);

    void step(int delay);

    void setDir(bool dir);

  private:
    byte _actM; // Переменная теперь является членом класса
    byte _dirM; // Переменная теперь является членом класса

};

#endif