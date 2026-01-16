#ifndef _MOSIKStep_h_
#define _MOSIKStep_h_

#include <Arduino.h>

class MOSIKStep {

  public:

    MOSIKStep(byte actM1, byte actM2, byte dirM1, byte dirM2, int Dbase, int mindel, int maxdel, float d);

    float step_acdec(float step);

    void przd_base(int step, bool isTurn, byte dir); 

    void przd_cm(float cm, byte dir);

    void turn(float deg, byte dir);

  private:

};

#endif