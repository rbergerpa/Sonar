#include "sonar.h"
#include <Arduino.h>

static const int MICROSECONDS_PER_INCH = 147;
static const double MICROSECONDS_PER_FOOT = MICROSECONDS_PER_INCH * 12.0;

Sonar::Sonar(byte _pin) {
  pin = _pin;
  PciManager.registerListener(pin, this);
}

int Sonar::inches() {
  return duration / MICROSECONDS_PER_INCH;
};

float Sonar::feet() {
  return duration / MICROSECONDS_PER_FOOT;
}

void Sonar::pciHandleInterrupt(byte vector) {
  byte val = digitalRead(pin);
  if (val == prevVal) {
    return;
  }
  prevVal = val;

  if (val == HIGH) {
    startTime = micros();
  }  else {
    duration = micros() - startTime;
  }
}

void startSonar(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(4);
    digitalWrite(pin, LOW);
    delay(4);
    pinMode(pin, INPUT);
}
