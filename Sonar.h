#ifndef SONAR_H
#define SONAR_H

#include <PciManager.h>

class Sonar : public PciListener {
private:
  byte pin;
  volatile byte prevVal;
  volatile unsigned long startTime;
  volatile unsigned long duration;

public:
  Sonar(byte pin);

  int inches();

  double feet();

  virtual void pciHandleInterrupt(byte vector);
};

extern void startSonar(int pin);
#endif
